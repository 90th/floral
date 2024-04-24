#ifndef SCENE_H
#define SCENE_H

// Abstract base class for scene rendering
class Scene {
public:
	// Render method to be implemented by derived classes
	virtual void Render() = 0;
};

#endif // SCENE_H
