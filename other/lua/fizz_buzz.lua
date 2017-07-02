require 'io'
function PrintBuzz(i)
	if (i % 3 == 0) then
		io.write("Fizz")
	end
	if (i % 5 == 0) then
		io.write("Buzz")
	end
	if ( ((i % 3) == 0) or ((i % 5) == 0)) then
		io.write("\n")
	end
end

for i=1, 100, 1 do
	PrintBuzz(i)
end
