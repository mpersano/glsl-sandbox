#include <Polycode.h>
#include <PolycodeView.h>

int
main()
{
	using namespace Polycode;

	auto view = new PolycodeView("foo");

	auto core = new POLYCODE_CORE(view, 480, 270, false, true, 0, 0, 90, 0, true);

	auto cs = CoreServices::getInstance();

	auto rm = cs->getResourceManager();
	rm->addDirResource("resources");

	auto scene = new Scene(Scene::SCENE_2D);
	scene->getActiveCamera()->setOrthoSize(core->getScreenWidth(), core->getScreenHeight());

	auto entity = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, core->getScreenWidth(), core->getScreenHeight());
	entity->setMaterialByName("Transition");

	scene->addChild(entity);

	auto binding = entity->getLocalShaderOptions();

	auto resolution = binding->addParam(ProgramParam::PARAM_VECTOR2, "resolution");
	auto level = binding->addParam(ProgramParam::PARAM_NUMBER, "level");

	resolution->setVector2(Vector2(core->getScreenWidth(), core->getScreenHeight()));

	Number t = 0;

	do {
		t += core->getElapsed();
		level->setNumber(.5f + .5f*sinf(.75*t));
	} while (core->updateAndRender());
}
