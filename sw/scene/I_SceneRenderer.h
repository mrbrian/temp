#pragma once

#include <vector>

class Color;
class I_KdTree;
class photon;

class I_SceneRenderer
{
public:
	virtual ~I_SceneRenderer(){};

    virtual Color *Render() = 0;
};
