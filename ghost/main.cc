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
	scene->getActiveCamera()->setOrthoSize(core->getScreenWidth(), core->getScreenHeight());

	auto entity = new pc::SceneImage("resources/knot.png");
	entity->setMaterialByName("Blur");

	scene->addChild(entity);

	auto binding = entity->getLocalShaderOptions();
	auto dist = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "dist");
	auto phase = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "phase");

	Number t = 0;

	do {
		t += 300.*core->getElapsed();
		const float f = 1.f/64.f;
		dist->setNumber((.5f + .5f*sinf(.01f*t))*f);
		phase->setNumber(.02f*t);
	} while (core->updateAndRender());
}
