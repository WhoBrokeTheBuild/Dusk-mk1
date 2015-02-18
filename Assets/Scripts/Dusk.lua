dusk_log_info("Initializing Dusk Classes");
dusk_log_info("Test?");

Dusk_Window = { }

Dusk_Window_methods = {

    getWidth = function( self )

        ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_width(ptr);

        end,
    getHeight = function( self )

        ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        return dusk_window_get_height(ptr);

        end,
    setWidth = function( self, width )

        ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_width(ptr, width);

        end,
    setHeight = function( self, height )

        ptr = rawget(rawget(getmetatable(self), "private"), "dusk_ptr");
        dusk_window_set_height(ptr, height);

        end
}

function Dusk_Window:new_field( key, value )
	dusk_log_error("Dusk_Window does not support new fields");
end

function Dusk_Window:dtor()
end

function Dusk_Window:ctor()
	local c = { }
	local c_mt = {
					__index = Dusk_Window_methods,
					__newindex = Dusk_Window.new_field,
					__gc = Dusk_Window.dtor,
					private = { }
				 }
	setmetatable(c, c_mt);

	rawset(rawget(getmetatable(c), "private"), "dusk_ptr", 0);

	return c
end

setmetatable(Dusk_Window, {__call = Dusk_Window.ctor});

Dusk_GS = {

    getWindow = function()

        win = Dusk_Window();
        rawset(rawget(getmetatable(win), "private"), "dusk_ptr", dusk_graphics_system_get_window());

        return win;

        end
}
