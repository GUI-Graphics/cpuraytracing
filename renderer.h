#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

namespace gui {
	class Scene;
	class Camera;

	class Renderer {
	public:
		Renderer(int samples) : smaples(samples)
		{ }

		void render(const Scene& scene, Camera& camera);

	public:
		int smaples;
	};
}

#endif
