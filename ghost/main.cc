#include <Polycode.h>
#include <PolycodeView.h>

int
main()
{
	namespace pc = Polycode;

	auto view = new pc::PolycodeView("foo");
	auto core = new pc::POLYCODE_CORE(view, 640, 480, false, true, 0, 0, 90, 0, true);

	auto cs = pc::CoreServices::getInstance();
	cs->getRenderer()->setClearColor(0, 0, 0, 0);

	auto rm = cs->getResourceManager();
	rm->addDirResource("resources");

	auto scene = new pc::Scene(pc::Scene::SCENE_2D);
	scene->getActiveCamera()->setOrthoSize(640, 480);

	auto entity = new pc::SceneImage("resources/knot.png");
	entity->setMaterialByName("Blur");

	scene->addChild(entity);

	auto binding = entity->getLocalShaderOptions();
	auto dist = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "dist");
	auto phase = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "phase");

	auto timer = 0;

	do {
		const float f = 1.f/64.f;
		dist->setNumber((.5f + .5f*sinf(.01f*timer))*f);

		phase->setNumber(.02f*timer);

		timer += 300.*core->getElapsed();
	} while (core->updateAndRender());
}
