#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "j1Window.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"
	Font = App->font->Load("fonts/ninja_naruto/njnaruto.ttf");

	display_floating_score.create("%i", 10);


	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	//// debug pathfing ------------------
	//static iPoint origin;
	//static bool origin_selected = false;

	//int x, y;
	//App->input->GetMousePosition(x, y);
	//iPoint p = App->render->ScreenToWorld(x, y);
	//p = App->map->WorldToMap(p.x, p.y);

	//if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	//{
	//	if(origin_selected == true)
	//	{
	//		App->pathfinding->CreatePath(origin, p);
	//		origin_selected = false;
	//	}
	//	else
	//	{
	//		origin = p;
	//		origin_selected = true;
	//	}
	//}


	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	//App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	x = x * 2;
	y = y * 2;
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					x, y);

	App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	//App->input->GetMousePosition(x, y);
	//iPoint p = App->render->ScreenToWorld(x, y);
	//p = App->map->WorldToMap(p.x, p.y);
	//p = App->map->MapToWorld(p.x, p.y);

	//App->render->Blit(debug_tex, p.x, p.y);

	//const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	//for(uint i = 0; i < path->Count(); ++i)
	//{
	//	iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
	//	App->render->Blit(debug_tex, pos.x, pos.y);
	//}

	//Logo ---------------------
	//App->render->Blit(App->gui->logo, 200, 100, &App->gui->rec_logo);

	// Gui ----------------------
	//App->gui->Print(windows, 0, 0, &home_window);
	score++;
	display_score.create("%i", score);
	App->gui->AddGuiButtons(0.3f, 1.05f, &App->gui->button_play, "1234",1);
	App->gui->AddGuiButtons(0.3f, 1.30f, &App->gui->button_options, "2345",2);
	App->gui->AddGuiButtons(0.3f, 1.55f, &App->gui->button_exit, "3456",3);

	App->gui->AddGuiButtons(1.05, 0.6, &App->gui->button_play, display_score.GetString(),4);	
	App->gui->AddGuiButtons(1.05, 1, &App->gui->button_play, "Score",5);
	
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		App->gui->AddFloatingScore(1.05, 0.3, {}, display_floating_score.GetString());
	}
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
	{
		tabstate++;
	}

	//posar que faci alguna cosa quant pases el ratol� per sobre
	//posar interfa� m�vil
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->tex->CleanUp();
	return true;
}
