#include "Deoptimization.h"
#include "R/Serialize.h"
#include "runtime/Code.h"

namespace rir {

FrameInfo FrameInfo::deserialize(const Opcode* anchor, SEXP refTable,
                                 R_inpstream_t inp) {
    FrameInfo info;
    info.code = Code::withUid(UUID::deserialize(refTable, inp));
    info.pc = info.code->code() + InInteger(inp);
    info.stackSize = InInteger(inp);
    info.inPromise = InInteger(inp);
    return info;
}

void FrameInfo::serialize(const Opcode* anchor, SEXP refTable,
                          R_outpstream_t out) const {
    code->uid.serialize(refTable, out);
    OutInteger(out, pc - code->code());
    OutInteger(out, stackSize);
    OutInteger(out, inPromise);
}

SEXP DeoptMetadata::deserialize(const Opcode* anchor, SEXP refTable,
                                R_inpstream_t inp) {
    unsigned numFrames = InInteger(inp);
    size_t size = sizeof(DeoptMetadata) + numFrames * sizeof(FrameInfo);
    SEXP store = Rf_allocVector(RAWSXP, size);

    DeoptMetadata* res = new (DATAPTR(store)) DeoptMetadata;
    res->numFrames = numFrames;
    for (unsigned i = 0; i < numFrames; i++)
        res->frames[i] = FrameInfo::deserialize(anchor, refTable, inp);

    return store;
}

void DeoptMetadata::serialize(const Opcode* anchor, SEXP refTable,
                              R_outpstream_t out) const {
    OutInteger(out, numFrames);
    for (unsigned i = 0; i < numFrames; i++)
        frames[i].serialize(anchor, refTable, out);
}

void DeoptMetadata::print(std::ostream& out) const {
    for (size_t i = 0; i < numFrames; ++i) {
        auto f = frames[i];
        out << f.code << "(" << f.code->uid.str() << ")"
            << "+" << f.pc - f.code->code() << " s" << f.stackSize;
        if (i < numFrames - 1)
            out << ", ";
    }
}

} // namespace rir
