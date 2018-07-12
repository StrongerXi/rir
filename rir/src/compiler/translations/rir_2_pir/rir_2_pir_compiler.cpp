#include "rir_2_pir_compiler.h"
#include "../../pir/pir_impl.h"
#include "R/RList.h"
#include "rir_2_pir.h"

#include "../../analysis/query.h"
#include "../../analysis/verifier.h"
#include "../../opt/cleanup.h"
#include "../../opt/delay_env.h"
#include "../../opt/delay_instr.h"
#include "../../opt/elide_env.h"
#include "../../opt/force_dominance.h"
#include "../../opt/inline.h"
#include "../../opt/scope_resolution.h"
#include "ir/BC.h"

#include <iostream>

#include "interpreter/runtime.h"

namespace rir {
namespace pir {

Rir2PirCompiler::Rir2PirCompiler(Module* module) : RirCompiler(module) {
    for (auto optimization : pirConfigurations()->pirOptimizations()) {
        translations.push_back(optimization->translator);
    }
}

void Rir2PirCompiler::compileClosure(SEXP closure, MaybeCls success,
                                     Maybe fail) {
    assert(isValidClosureSEXP(closure));
    DispatchTable* tbl = DispatchTable::unpack(BODY(closure));

    if (tbl->available(1)) {
        if (isVerbose())
            std::cerr << "Closure already compiled to PIR\n";
    }

    auto formals = RList(FORMALS(closure));

    std::vector<SEXP> arg_names;
    std::vector<SEXP> default_args;
    for (auto it = formals.begin(); it != formals.end(); ++it) {
        // TODO: support default arguments
        default_args.push_back(*it);
        arg_names.push_back(it.tag());
    }

    rir::Function* srcFunction = tbl->first();
    compileClosure(srcFunction, arg_names, default_args,
                   module->getEnv(CLOENV(closure)), success, fail);
}

void Rir2PirCompiler::compileFunction(rir::Function* srcFunction,
                                      const std::vector<SEXP>& arg_names,
                                      const std::vector<SEXP>& default_args,
                                      MaybeCls success, Maybe fail) {
    compileClosure(srcFunction, arg_names, default_args, Env::notClosed(),
                   success, fail);
}

void Rir2PirCompiler::compileClosure(rir::Function* srcFunction,
                                     const std::vector<SEXP>& arg_names,
                                     const std::vector<SEXP>& default_args,
                                     Env* closureEnv, MaybeCls success,
                                     Maybe fail) {
    // TODO: Support default arguments
    for (auto d : default_args)
        if (d != R_MissingArg)
            return fail();

    // TODO: Support elipsis argument
    for (auto d : arg_names)
        if (d == R_DotsSymbol)
            return fail();
    
    bool failed = false;
    module->createIfMissing(
        srcFunction, arg_names, closureEnv, [&](Closure* pirFunction) {
            Builder builder(pirFunction, closureEnv);
            Rir2Pir rir2pir(*this, srcFunction);
            if (rir2pir.tryCompile(srcFunction->body(), builder)) {
                if (isVerbose()) {
                    std::cout << " ========= Done compiling " << srcFunction
                              << "\n";
                    builder.function->print(std::cout);
                    std::cout << " ==========\n";
                }
                if (!Verify::apply(pirFunction)) {
                    failed = true;
                    if (isVerbose()) {
                        std::cout << " Failed verification after p2r compile "
                                  << srcFunction << "\n";
                    }
                    assert(false);
                    return false;
                }
                return true;
            }
            failed = true;
            if (isVerbose()) {
                std::cout << " Failed p2r compile " << srcFunction << "\n";
            }
            return false;
        });

    if (failed)
        fail();
    else
        success(module->get(srcFunction));
}

void Rir2PirCompiler::optimizeModule() {
    size_t passnr = 0;
    bool verbose = isVerbose();

    module->eachPirFunction([&](Module::VersionedClosure& v) {
        auto f = v.current();
        if (verbose)
            v.saveVersion();
        applyOptimizations(f, "Optimizations 1st Pass");
        applyOptimizations(f, "Optimizations 2nd Pass");
    });

    for (int i = 0; i < 5; ++i) {
        module->eachPirFunction([&](Module::VersionedClosure& v) {
            auto f = v.current();
            if (verbose)
                v.saveVersion();
            Inline::apply(f);
            if (verbose)
                printAfterPass("inline", "Inlining", f, passnr++);
            applyOptimizations(f, "Optimizations After Inlining");
        });
    }
}

void Rir2PirCompiler::printAfterPass(const std::string& pass,
                                     const std::string& category, Closure* f,
                                     size_t passnr) {
    std::cout << "============== " << category << ": " << pass
              << " == " << passnr << " ======================\n";
    f->print(std::cout);
}

void Rir2PirCompiler::applyOptimizations(Closure* f,
                                         const std::string& category) {
    size_t passnr = 0;
    for (auto& translation : this->translations) {
        translation->apply(f);
        if (isVerbose())
            printAfterPass(translation->getName(), category, f, passnr++);
#if 0
        assert(Verify::apply(f));
#endif
    }
    assert(Verify::apply(f));
}

} // namespace pir
} // namespace rir
