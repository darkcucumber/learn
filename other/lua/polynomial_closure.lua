-- lets create a polynomial closure
-- takes coefficients and returns a polynomial function 
-- that can be evaluated on a single argument
makePoly = 
function (coeffs)
	return (
		function(x)
			sum = 0
			i = 0
			for key, value in pairs(coeffs)
			do
				sum = sum + math.pow(x, i) * value
				i = i + 1
			end
			return sum 
		end)
end

polynomial = makePoly({1, 1, 1})
print(polynomial(2))