require 'torch'
require 'nn'
require 'csvigo'
mnist = require 'mnist'
require 'image'
require 'optim'

fullset = mnist.traindataset()
testset = mnist.testdataset()

print(fullset)
print(testset)

trainset = {
	size = 50000,
	data = fullset.data[{{1, 50000}}]:double(),
	label = fullset.label[{{1, 50000}}]
}

validationSet = {
	size = 10000,
	data = fullset.data[{{50001, 60000}}]:double(),
	label = fullset.label[{{50001, 60000}}]
}

print(trainset)

-- create the network
input = 28 * 28
params1 = 40
params2 = 10
loss = nn.ClassNLLCriterion()
mlp = nn.Sequential()
layer1 = nn.Linear(input, params1)
layer2 = nn.Linear(params1, params2)
mlp:add(layer1)
mlp:add(nn.Tanh())
mlp:add(layer2)
mlp:add(nn.LogSoftMax())
print(mlp)
function gradUpdate(mlp, x, y, criterion, learningRate)
	x = x:view(28 * 28)
    local pred = mlp:forward(x)
    local err = criterion:forward(pred, y)
    local gradCriterion = criterion:backward(pred, y)
    mlp:zeroGradParameters()
    mlp:backward(x, gradCriterion)
    mlp:updateParameters(learningRate)
end

function gradBatchUpdate(mlp, batch_size, criterion, learningRate)
	local batch = batch_size or 200
	local shuffle = torch.randperm(trainset.size)

	for t=1,trainset.size,batch do
		local size = math.min(t + batch - 1, trainset.size) - t
		inputs = torch.Tensor(size, 28, 28)
		targets = torch.Tensor(size)
		local targets = torch.Tensor(size)
		for i=1,size do
			local input = trainset.data[shuffle[i+t]]
			local target = trainset.label[shuffle[i+t]]
			inputs[i] = input
			targets[i] = target
		end
		-- the loss function requires n>=target>0
		targets:add(1)
		inputs = inputs:view(size, 28 * 28)
		local pred = mlp:forward(inputs)
		local err = criterion:forward(pred, targets)
		local gradCriterion = criterion:backward(pred, targets)
		mlp:zeroGradParameters()
		mlp:backward(inputs, gradCriterion)
		mlp:updateParameters(learningRate)
	end
end



function eval(dataset, model, batch_size)
	local count = 0
	batch_size = batch_size or 200
	for i=1,dataset.size,batch_size do
		local size = math.min(i + batch_size - 1, dataset.size) - i
		local inputs = dataset.data[{{i, i + size - 1}}]
		inputs = inputs:view(size, 28 * 28)
		local targets = dataset.label[{{i, i + size - 1}}]:long()
		local outputs = model:forward(inputs)
		local _, indices = torch.max(outputs, 2)
		indices:add(-1)
		local guessed_right = indices:eq(targets):sum()
		count = count + guessed_right
	end
	return count / dataset.size

end

for i=1,100 do
	gradBatchUpdate(mlp, 200, loss, 0.001)
end

print(eval(validationSet, mlp, 200))