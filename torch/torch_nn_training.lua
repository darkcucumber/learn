-- X: design matrix -> size m x n (m n-dimensional data vectors)
-- Y: classes -> size m x K (m K-dimensional data vectors)
require 'torch'

etha = 0.01

-- SGD
for i = 1, m do
	local pred = net:forward(X[i])
	local err = loss:forward(pred, Y[i])
	local gradLoss = loss:backward(pred, Y[i])
	net:zeroGradParameters()
	net:backward(X[i], gradLoss)
	net:updateParameters(etha)
end

-- Mini-batch GD - better in terms of convergence for multi-dim input
for i = 1, m, batchSize do
	net:zeroGradParameters()
	for j = 0, batchSize - 1 do
		if i + j > m then break end
		local pred = net:forward(X[i])
		local err = loss:forward(pred, Y[i])
		local gradLoss = loss:backward(pred, Y[i])
		net:backward(X[i], gradLoss)
	end
	net:updateParameters(etha)
end

-- produce a dataset
local dataset = {}
function dataset:size() return m end
for i=1, m do dataset[i] = {X[i], Y[i]} end

-- train stuff with a provided network and loss function
local trainer = nn.StochasticGradient(net, loss)
trainer:train(dataset)
