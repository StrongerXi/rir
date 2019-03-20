#include "visibility.h"
#include "R/Funtab.h"

namespace rir {
namespace pir {

AbstractResult VisibilityAnalysis::apply(LastVisibilityUpdate& vis,
                                         Instruction* i) const {
    AbstractResult res;
    auto isVisibilityChanging = [&]() {
        if (vis.last != i) {
            vis.last = i;
            vis.observable.clear();
            res.update();
        }
    };
    switch (i->tag) {
    case Tag::Invisible:
    case Tag::Visible:
        isVisibilityChanging();
        break;
    case Tag::CallBuiltin:
    case Tag::CallSafeBuiltin:
        int builtinId;
        if (auto c = CallBuiltin::Cast(i)) {
            builtinId = c->builtinId;
        } else {
            builtinId = CallSafeBuiltin::Cast(i)->builtinId;
        }

        if (builtinUpdatesVisibility(builtinId)) {
            isVisibilityChanging();
        }
        break;
    default:
        if (i->exits() && vis.last) {
            vis.observable.insert(vis.last);
            res.update();
        }
    }
    return res;
};

} // namespace rir
} // namespace pir
