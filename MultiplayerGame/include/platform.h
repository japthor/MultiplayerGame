#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "object.h"

class Platform: public Object {
public:
    /// Desstructor
  ~Platform() {};
    /// Constructor
  Platform(Vec2 position, Vec2 scale, BodyType type, float32 density,
			     float32 friction, char* texture, Vec2 spriteOrigin);
    
  /// Init
  virtual void Init()  override{};
  /// Input
  virtual void Input()override{};
	/// Update
  virtual void Update() override{};
  /**
  * Collision with other objects
  * @param instigator Objects name to collide with.
  */
  virtual void Collision(Object* instigator) override {};
  /// Type of object
  virtual DefineType getDefineType() override;

};

#endif //__PLATFORM_H__
