#include <Polycode.h>
#include <PolycodeView.h>

int
main()
{
	using namespace Polycode;

	auto view = new PolycodeView("foo");

	auto core = new POLYCODE_CORE(view, 640, 480, false, true, 0, 0, 90, 0, true);

	auto cs = CoreServices::getInstance();

	auto rm = cs->getResourceManager();
	rm->addDirResource("resources");

	auto scene = new Scene(Scene::SCENE_2D);
	scene->getActiveCamera()->setOrthoSize(640, 480);

	auto entity = new ScenePrimitive(ScenePrimitive::TYPE_VPLANE, 480, 270);
	entity->setMaterialByName("Transition");

	scene->addChild(entity);

	auto binding = entity->getLocalShaderOptions();

	auto level = binding->addParam(ProgramParam::PARAM_NUMBER, "level");

	Number t = 0;

	for (;;) {
		t += core->getElapsed();

		level->setNumber(.5f + .5f*sinf(2.*t));

		if (!core->updateAndRender())
			break;
	}
}
