#include <Polycode.h>
#include <PolycodeView.h>

namespace pc = Polycode;

class test
{
public:
	test(pc::PolycodeView *view);

	bool update();

private:
	pc::Core *core_;

	pc::LocalShaderParam *dist_param_;
	pc::LocalShaderParam *phase_param_;

	Number timer_;
};

test::test(pc::PolycodeView *view)
: core_ { new pc::POLYCODE_CORE(view, 640, 480, false, true, 0, 0, 90, 0, true) }
, timer_ { 0 }
{
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
	dist_param_ = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "dist");
	phase_param_ = binding->addParam(pc::ProgramParam::PARAM_NUMBER, "phase");
}

bool
test::update()
{
	const float f = 1.f/64.f;

	dist_param_->setNumber((.5f + .5f*sinf(.01f*timer_))*f);
	phase_param_->setNumber(.02f*timer_);

	timer_ += 300.*core_->getElapsed();

	return core_->updateAndRender();
}

int
main()
{
	test t { new pc::PolycodeView("foo") };

	while (t.update())
		;
}
