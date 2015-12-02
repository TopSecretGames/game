#ifndef IBASE_EFFECT_H
#define IBASE_EFFECT_H
#include <string>

namespace tsg {
namespace effect {
class IBaseEffect {
 public:
  virtual std::string getName() = 0;
  virtual void update(float time) = 0;
  virtual bool isFinished() = 0;
  virtual ~IBaseEffect(){};
};
}
}
#endif
