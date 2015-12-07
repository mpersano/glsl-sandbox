#include <Polycode.h>
#include <PolycodeView.h>

int
main()
{
	using namespace Polycode;

	auto view = new PolycodeView("foo");
	auto core = new POLYCODE_CORE(view, 480, 270, false, true, 0, 0, 90, 0, true);

	auto cs = CoreServices::getInstance();
	cs->getRenderer()->setClearColor(0, 0, 0, 0);

	auto rm = cs->getResourceManager();
	rm->addDirResource("resources");

	auto scene = new Scene(Scene::SCENE_2D);
	scene->getActiveCamera()->setOrthoSize(core->getScreenWidth(), core->getScreenHeight());

	auto entity = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, core->getScreenWidth(), core->getScreenHeight());
	entity->setMaterialByName("Ripple");

	scene->addChild(entity);

	auto binding = entity->getLocalShaderOptions();
	auto center = binding->addParam(ProgramParam::PARAM_VECTOR2, "center");
	auto radius = binding->addParam(ProgramParam::PARAM_NUMBER, "radius");
	auto width = binding->addParam(ProgramParam::PARAM_NUMBER, "width");

	center->setVector2(Vector2(.5*core->getScreenWidth(), .5*core->getScreenHeight()));
	width->setNumber(30);

	Number t = 0;

	do {
		t += core->getElapsed();
		radius->setNumber(fmod(200.*t, 400.));
	} while (core->updateAndRender());
}
