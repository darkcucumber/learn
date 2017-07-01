require 'table'

function map_function(func, list)
	results = {}
	for key, value in pairs(list) do
		results[key] = func(value)
	end
	return results
end

function filter_function(func, list)
	results = {}
	for key, value in pairs(list) do
		if (func(value)) then results[#results + 1] = value end
	end
	return results
end


-- Haskell-like foldl  ( (b -> a -> b) -> b -> [a] -> b)
function foldl_function(func, accumulator, list)
	for key, value in pairs(list) do
		accumulator = func(accumulator, value)
	end
	return accumulator
end

-- Haskell-like foldr ( (a -> b -> b) -> b -> [a] -> b)
function foldr_function(func, accumulator, list)
	for i = #list, 1, -1 do
		accumulator = func(list[i], accumulator)
	end
	return accumulator
end

----- examples ----------
for key, value in pairs(map_function(function(x) return x + 1 end, 
									{1, 2, 3}))
do
	print(value)
end
print()

for key, value in pairs(filter_function(function(x) return x < 10 end, 
									{1, 2, 3, 55, 66, 9}))
do
	print(value)
end

print()


print(foldl_function(function(a, x) return a - x end, 0, {1, 2, 3}))

print(foldr_function(function(x, a) return a - x end, 0, {1, 2, 3}))
