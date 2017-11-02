#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	red_bumper = green_bumper = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load Assets requirede for "map"
	background = App->textures->Load("pinball/background.png");
	red_bumper = App->textures->Load("pinball/redbump.png");
	green_bumper = App->textures->Load("pinball/greenbump.png");
	flipper = App->textures->Load("pinball/paletas.png");
	pinball = App->textures->Load("pinball/ball.png");
	App->audio->PlayMusic("music.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT+50, SCREEN_WIDTH, 40);
	sensor->listener = App->player;
	// Create Level collisions
	
	int pinball[126] = {
		221, 660,
		221, 652,
		324, 621,
		324, 585,
		257, 605,
		251, 590,
		324, 567,
		325, 352,
		280, 335,
		323, 204,
		324, 178,
		321, 152,
		312, 125,
		297, 101,
		277, 80,
		256, 64,
		260, 58,
		278, 72,
		296, 88,
		312, 110,
		322, 128,
		328, 145,
		331, 170,
		331, 185,
		331, 574,
		349, 580,
		366, 575,
		365, 168,
		361, 141,
		352, 118,
		340, 93,
		324, 69,
		299, 44,
		268, 25,
		231, 10,
		193, 4,
		152, 7,
		111, 20,
		78, 40,
		51, 65,
		31, 92,
		17, 122,
		9, 153,
		6, 189,
		9, 216,
		13, 232,
		71, 403,
		57, 406,
		48, 412,
		41, 423,
		41, 432,
		30, 432,
		16, 437,
		8, 448,
		6, 459,
		6, 607,
		151, 651,
		151, 660,
		0, 660,
		0, 0,
		371, 0,
		371, 660,
		221, 661
	};

		stage.add(App->physics->CreateChain(0, 0, pinball, 126, b2_staticBody));
	
	
		int pinballa[14] = {
			47, 480,
			40, 480,
			40, 583,
			118, 605,
			122, 590,
			47, 567,
			47, 481
		};

		stage.add(App->physics->CreateChain(0, 0, pinballa, 14, b2_staticBody));
	
	
		int pinballb[12] = {
			260, 551,
			283, 545,
			287, 541,
			290, 536,
			290, 476,
			260, 550
		};

		stage.add(App->physics->CreateChain(0, 0, pinballb, 12, b2_staticBody));
	
	
		int pinballc[60] = {
			88, 147,
			101, 121,
			122, 100,
			142, 88,
			168, 80,
			186, 78,
			215, 82,
			237, 92,
			257, 106,
			272, 124,
			283, 146,
			288, 162,
			290, 179,
			289, 195,
			284, 219,
			280, 214,
			283, 197,
			284, 175,
			279, 151,
			268, 130,
			254, 112,
			234, 97,
			215, 89,
			190, 84,
			164, 87,
			139, 96,
			121, 108,
			105, 125,
			93, 150,
			89, 147
		};

		stage.add(App->physics->CreateChain(0, 0, pinballc, 60, b2_staticBody));
	
	
		int pinballd[34] = {
			111, 59,
			114, 65,
			92, 80,
			71, 105,
			53, 141,
			47, 172,
			47, 198,
			49, 213,
			107, 388,
			102, 392,
			43, 216,
			40, 182,
			43, 157,
			52, 127,
			70, 96,
			85, 78,
			111, 60
		};

		stage.add(App->physics->CreateChain(0, 0, pinballd, 34, b2_staticBody));
	
		int pinballe[14] = {
			81, 475,
			81, 536,
			85, 542,
			91, 546,
			112, 551,
			112, 545,
			83, 475
		};

		stage.add(App->physics->CreateChain(0, 0, pinballe, 14, b2_staticBody));

		int bumper_left[6] = {
			84, 475,
			117, 547,
			116, 544
		};

		bumpers.add(App->physics->CreateChain(0, 0, bumper_left, 6, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		int bumper_right[6] = {
			290, 473,
			258, 547,
			259, 547
		};

		bumpers.add(App->physics->CreateChain(0, 0, bumper_right, 6, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		//3 up top

		bumpers.add(App->physics->CreateCircle(185, 55, 9, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		//3 red up ones

		bumpers.add(App->physics->CreateCircle(122, 135, 15, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		bumpers.add(App->physics->CreateCircle(188, 103, 15, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		bumpers.add(App->physics->CreateCircle(255, 135, 15, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		//2 middle ones
		bumpers.add(App->physics->CreateCircle(190, 205, 9, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		bumpers.add(App->physics->CreateCircle(105, 284, 9, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.1f);

		bumpers.add(App->physics->CreateCircle(252, 284, 9, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(1.5f);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	// All draw functions ------------------------------------------------------
	App->renderer->Blit(background, 0, 0, NULL, 1.0f);

	p2List_item<PhysBody*>* c = bumpers.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		
		if (c->data->width == 15)
		{
			x -= c->data->width / 3;
			y -= c->data->height / 3;
			App->renderer->Blit(red_bumper, x+3, y+3, NULL, 1.0f, c->data->GetRotation());
		}
		if (c->data->width == 9)
		{
			x -= c->data->width / 2;
			y -= c->data->height / 2;
			App->renderer->Blit(green_bumper, x, y, NULL, 1.0f, c->data->GetRotation());
		}

		c = c->next;
	}

	for (int i = 0; i < 4; i++) {
		int x, y;
		App->player->bouncers[i].cpbody->GetPosition(x, y);
		x -= 56;
		y -= 56;
		
		switch (i) {
		case 0:
			App->renderer->Blit(flipper, x, y, NULL, 1.0f, App->player->bouncers[i].flipperpbody->GetRotation() - DEGTORAD * 50, INT_MAX, INT_MAX, false, 0.9f);
			break;
		case 1:
			App->renderer->Blit(flipper, x, y, NULL, 1.0f, App->player->bouncers[i].flipperpbody->GetRotation() + DEGTORAD * 50, INT_MAX, INT_MAX, false, 0.7f);
			break;
		case 2:
			App->renderer->Blit(flipper, x, y, NULL, 1.0f, App->player->bouncers[i].flipperpbody->GetRotation() + DEGTORAD * 50, INT_MAX, INT_MAX, true, 0.7f);
			break;
		case 3:
			App->renderer->Blit(flipper, x, y, NULL, 1.0f, App->player->bouncers[i].flipperpbody->GetRotation() + DEGTORAD * 50, INT_MAX, INT_MAX, true, 0.9f);
			break;
		}
	}
	
	int x, y;
	App->player->ball.getLast()->data->GetPosition(x,y);
	App->renderer->Blit(pinball, x, y, NULL, 1.0f, App->player->ball.getLast()->data->GetRotation());

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
}
