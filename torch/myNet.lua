require 'math'
require 'torch'
require 'nn'
require 'gnuplot'


dataLen = 100000
testData = 1000
lr = 0.05

dataX = torch.rand(dataLen, 1) * 5
dataY = torch.rand(dataLen, 1) * 5
preds = torch.Tensor(testData, 1)

dataY = dataX:clone():apply(function(x) return torch.ceil(x % 5) end)

dataTestX =  torch.rand(testData, 1) * 5

-- create the network
require 'nn'
net = nn.Sequential()
module1 = nn.Linear(1, 15)
module2 = nn.Linear(15, 15)
module3 = nn.Linear(15, 5)
module4 = nn.Linear(5, 1)

errorFunction = nn.MSECriterion()
net:add(module1) net:add(nn.Tanh())
net:add(module2) net:add(nn.Tanh())
net:add(module3) net:add(nn.SoftMax())
net:add(module4)


print("Training the net")
epochs = 4
for epoch=0,epochs,1 do
	if epoch % 10 == 0 then
		print(string.format("Epoch %d", epoch))
	end
	
		for j=1,dataLen,1 do
			-- index = math.min(torch.floor(torch.rand(1) * dataLen + 1)[1], dataLen)
			index = j
			pred = net:forward(dataX[index])
			err = errorFunction:forward(pred, dataY[index])
			if j == 1 then
			print(err) end
			gradLoss = errorFunction:backward(pred, dataY[index])
			net:zeroGradParameters()
			-- print(string.format("Index %d f(%f) = %f error %f    %f", index, dataX[index][1], pred[1], err, dataY[index][1]))
			net:backward(dataX[index], gradLoss)	
			net:updateParameters(lr)
		end

		
	
end
print("Finished training the net")

dataX:resize(dataLen)
dataY:resize(dataLen)

-- make predictions
print("Making predictions")
for i=1, testData, 1 do
	preds[i] = net:forward(dataTestX[i])
	-- print(string.format("f(%f) = %f", dataTestX[i][1], preds[i][1]))
end

print("Plotting figures")
gnuplot.figure(1)
gnuplot.plot(
			{'Training set', dataX, dataY, '.'},
			 {'Test set', dataTestX:view(testData), preds:view(testData), '+'})
-- gnuplot.figure(2)
-- gnuplot.plot('Error in iteration', torch.Tensor(errorsX), torch.Tensor(errorsY), '.')