dusk_log_info("Initializing Dusk Classes");

Dusk = { }
Dusk.Graphics = { }

-- Dusk::Graphics::GraphicsSystem

Dusk.Graphics.GraphicsSystem = {

    getWindow = function()

        local win = Dusk.Graphics.Window();
        rawset(rawget(getmetatable(win), "private"), "dusk_ptr", dusk_graphics_system_get_window());

        return win;

        end,
    getShaderManager = function()

        local sm = Dusk.Graphics.ShaderManager();
        rawset(rawget(getmetatable(sm), "private"), "dusk_ptr", dusk_graphics_system_get_shader_manager());

        return sm;

        end
}

-- Dusk::Graphics::Window

Dusk.Graphics.Window = { }
Dusk.Graphics.Window.methods = {

    getWidth = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_width(ptr);

        end,
    getHeight = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_height(ptr);

        end,
    setWidth = function( self, width )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_width(ptr, width);

        end,
    setHeight = function( self, height )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_height(ptr, height);

        end,
    getTitle = function( self )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_title(ptr);

        end,
    setTitle = function( self, title )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_title(ptr, title);

        end
}

function Dusk.Graphics.Window:new_field( key, value )
	dusk_log_error("Dusk.Graphics.Window does not support new fields");
end

function Dusk.Graphics.Window:dtor()
end

function Dusk.Graphics.Window:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Graphics.Window.methods,
					__newindex = Dusk.Graphics.Window.new_field,
					__gc = Dusk.Graphics.Window.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(Dusk.Graphics.Window, {__call = Dusk.Graphics.Window.ctor});

-- Dusk.Graphics.ShaderManager

Dusk.Graphics.ShaderManager = { }
Dusk.Graphics.ShaderManager.methods = {

    loadProgram = function( self, name, verts, frags )

        local ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_shader_manager_load_program(ptr, name, verts, frags);

        end

}

function Dusk.Graphics.ShaderManager:new_field( key, value )
	dusk_log_error("Dusk.Graphics.ShaderManager does not support new fields");
end

function Dusk.Graphics.ShaderManager:dtor()
end

function Dusk.Graphics.ShaderManager:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk.Graphics.ShaderManager.methods,
					__newindex = Dusk.Graphics.ShaderManager.new_field,
					__gc = Dusk.Graphics.ShaderManager.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(Dusk.Graphics.ShaderManager, {__call = Dusk.Graphics.ShaderManager.ctor});
