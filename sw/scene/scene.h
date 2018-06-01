#pragma once

#include <algebra.h>
#include <camera.h>
#include <misc.h>
#include <photon.h>
#include <polyroots.h>
#include <shapes.h>
#include <vector>

class I_KdTree;
class ImagePlane;
class Light;

using namespace std;

struct SurfacePoint
{
public:
    Point3D position;
    Vector3D normal;
    Material *material;

    SurfacePoint() {}

    SurfacePoint(Point3D p, Vector3D v, Material *m)
    {
        position = p;
        normal = v;
        material = m;
    }
};

struct Ray
{
public:
    Point3D origin;
    Vector3D direction;

    Ray(Point3D p, Vector3D v)
    {
        origin = p;
        direction = v;
    }
};

class Scene
{
public:
    enum RayType
    {
        Diffuse,
        Specular,
        Transmission
    };

    Scene();
    ~Scene();

    static Scene *planeScene(int width, int height);
    static Scene *cornellBoxScene(int width, int height);

    Color *Render();
    Color *Render(vector<photon*> *photon_map);
    Color *Render(I_KdTree *kd);
    Color Render(I_KdTree *kd, int x, int y);

    bool trace_ray(I_KdTree *kd, Ray ray, Color *color, int depth);
    bool trace_ray(Point3D o, Vector3D v, Color *color, int depth);
    bool trace_ray_lights(Point3D o, Vector3D v, Color *color, int depth);
    bool trace_ray(Point3D o, Vector3D v, Color *color, Point3D *out_pos, Vector3D *out_norm, Color *out_clr, Material *out_mat, int depth);
    bool trace_primary_ray(Point3D in_pos, Vector3D in_dir, Color *in_clr, Point3D *_out_pos, Vector3D *_out_norm, Vector3D *_out_reflect, Vector3D *_out_refract, Color *_out_clr, Material *_out_mat);
    Point2D calc_image_coords(Point3D pt);

    // collide photon with the scene objects
    Color BRDF(SurfacePoint &x, Vector3D &view, Vector3D &pd);
    void initialize_photons(int num_photons, vector<photon*> *out_photons);
    RayType russian_roulette(Material *mat);
    void emit_photons(int num_photons, vector<photon*> *photon_map);
    void trace_photon(photon *in_pho, int depth, vector<photon*> *out_list);
    void bounce_photon(RayType ray_type, Point3D *i_pos, Vector3D *i_norm, Vector3D *i_reflect, Vector3D *i_refract, Color *i_clr, double energy, int depth, vector<photon*> *out_list);
    Color radiance_estimate(I_KdTree *kd, SurfacePoint end_pt);

    void Transform(Matrix4x4 m);

    Camera cam;
    ImagePlane *imgPlane;
    std::vector<SceneObject*> objects;
    std::vector<Light*> lights;
};

void BuildOrthonormalSystem(const Vector3D& v1, Vector3D& v2, Vector3D& v3);
Vector3D HemisphereSampling(Vector3D m_normal);
