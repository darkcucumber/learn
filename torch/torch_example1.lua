require 'torch'
N = 5

-- produce a random NxN matrix
A = torch.rand(N, N)

-- A = A * (transpose(A))
-- we make A symmetric positive
A = A * A:t()

-- make it definite
A:add(0.001, torch.eye(N))

-- add a linear term
b = torch.rand(N)

-- create the quadratic form (closure to global scope)
function J(x)
	return 0.5 * x:dot( A * x ) - b:dot( x )
end

-- compute on a random point
print( J( torch.rand(N) ) )

-- let us search for the minimum of J
function dJ(x)
	return A * x - b
end

-- gradient descent optimizer (closure)
function gradDesc(lr)

	return (
		function (dJ, x)
			for i=1,200000,1 do
				x = x - lr * dJ(x)
				print(string.format('at iter %d J(x) = %f', i, J(x)))
			end
		end)

end


learning_rate = 0.01
gradient = gradDesc(learning_rate)

x = torch.rand(N) -- 'current solution'
gradient(dJ, x)


