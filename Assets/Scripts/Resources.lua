dusk_log_info("Loading Resources");

local sm = Dusk.Graphics.GraphicsSystem.getShaderManager();

sm:loadProgram( "flat", "Assets/Shaders/flat.fs.glsl", "Assets/Shaders/flat.vs.glsl" );
sm:loadProgram( "skybox", "Assets/Shaders/skybox.fs.glsl", "Assets/Shaders/skybox.vs.glsl" );
sm:loadProgram( "entity", "Assets/Shaders/entity.fs.glsl", "Assets/Shaders/entity.vs.glsl" );
