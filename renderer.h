#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

namespace gui {
	class Scene;
	class Camera;

	class Renderer {
	public:
		Renderer(int samples) : samples(samples)
		{ }

		void render(const Scene& scene, Camera& camera) const;
		Vector3 radiance(const Ray& ray, const Scene& scene, int depth) const;

	public:
		int samples;
		static long long nIntersects;
	};
}

#endif
