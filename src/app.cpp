#include "app.h"

#include <nikola/nikola.h>

/// ----------------------------------------------------------------------
/// App
struct nikola::App {
  nikola::Window* window; 

  nikola::FrameData frame_data;
  nikola::RenderQueue render_queue; 

  nikola::u16 resource_group;

  bool has_editor = false;
};
/// App
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// Private functions

static void init_resources(nikola::App* app) {
  // Resource group init
  nikola::FilePath res_path = nikola::filepath_append(nikola::filesystem_current_path(), "res");
  app->resource_group       = nikola::resources_create_group("app_res", res_path);
}

/// Private functions
/// ----------------------------------------------------------------------

/// ----------------------------------------------------------------------
/// App functions 

nikola::App* app_init(const nikola::Args& args, nikola::Window* window) {
  // App init
  nikola::App* app = new nikola::App{};

  // Window init
  app->window = window;

  // Camera init
  float aspect_ratio = nikola::window_get_aspect_ratio(app->window);
  nikola::camera_create(&app->frame_data.camera, aspect_ratio, nikola::Vec3(10.0f, 0.0f, 10.0f), nikola::Vec3(-3.0f, 0.0f, 0.0f));

  // GUI init
  nikola::gui_init(window);

  // Resources init
  init_resources(app);

  return app;
}

void app_shutdown(nikola::App* app) {
  nikola::gui_shutdown();

  delete app;
}

void app_update(nikola::App* app, const nikola::f64 delta_time) {
  // Quit the application when the specified exit key is pressed
  if(!nikola::input_key_pressed(nikola::KEY_ESCAPE)) {
    nikola::event_dispatch(nikola::Event{.type = nikola::EVENT_APP_QUIT});
    return;
  }

  // Disable/enable the GUI
  if(nikola::input_key_pressed(nikola::KEY_F1)) {
    app->has_editor                  = !app->has_editor;
    app->frame_data.camera.is_active = !app->has_editor;

    nikola::input_cursor_show(app->has_editor);
  }

  // Update the camera
  nikola::camera_update(app->frame_data.camera);
}

void app_render(nikola::App* app) {
  // nikola::renderer_begin(app->frame_data);
  // All 3D rendering commands go here...
  // nikola::renderer_end();
  
  // nikola::batch_renderer_begin();
  // All 2D rendering commands go here...
  // nikola::batch_renderer_end();
}

void app_render_gui(nikola::App* app) {
  if(!app->has_editor) {
    return;
  }

  nikola::gui_begin();

  // GUI functions go here...

  nikola::gui_end();
}

/// App functions 
/// ----------------------------------------------------------------------
