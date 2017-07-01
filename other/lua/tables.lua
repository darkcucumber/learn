require 'math'

days = {"Monday", "Tuesday"}
print( days[1] )

a = {x = "head", y = "balance"}
print( a.x )

polyDef = {	color = "blue",	-- polyDef['color'], polyDef.color
			thickness = 2, 	-- polyDef['thickness'], polyDef.thickness
			{x = 0, y = 1}, -- polyDef[1]
			{x = 2, y = 3}} -- polyDef[2]
print( polyDef.color )
print( polyDef[1].x )
print( polyDef[2].y )

a = {[3] = 'three', [1] = 'one'}
print( a[2] ) -- nil
print( a[3] ) -- 'three'

funcLib = {
	["add"] = function(x, y) return x + y end,
	["subtract"] = function (x, y) return x - y end,
	["multiply"] = function (x, y) return x * y end,
	["divide"] = function (x, y) if y ~= 0 then return x / y else error("zero division attempt") end
	end
}

print( funcLib.add(1, 2) )
print( funcLib.divide(1, 2 - funcLib.multiply(1, 3)) )