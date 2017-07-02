require 'torch'
require 'optim' -- run '$ luarocks install optim'

N = 5

A = torch.rand(N, N)

-- make it symmetric positive
A = A*A:t()

-- make it definite
A:add(0.001, torch.eye(N))

b = torch.rand(N)

function J(x)
	return 0.5 * x:dot(A * x) - b:dot(x)
end

function dJ(x)
	return A * x - b
end

-- gradient descent optimizer (closure)
function gradDesc(lr)

	return (
		function (dJ, x)
			for i=1,20000,1 do
				-- remember to update all elements of the tensor simultaneously
				-- copy the current version
				prex = x
				-- update the tensor
				x = prex - lr * dJ(prex)
				print(string.format('at iter %d J(x) = %f with lr %f', i,   J(x), lr))
			end
		end)

end

do
	local neval = 0
	local N = 5
	-- conjugate gradient descent parameters
	local state = {
		verbose = true,
		maxIter = 100
	}

	function JdJ(x)
		local Jx = J(x)
		neval = neval + 1
		print(string.format('after %d evaluations J(x) = %f', neval, Jx))
		return Jx, dJ(x)
	end

	x = torch.rand(N)
	x2 = x


	-- hand written gd
	learning_rate = 0.01
	gradient = gradDesc(learning_rate)

	gradient(dJ, x)	

	-- conjugate gradient descent using optim
	optim.cg(JdJ, x2, state)	
end



