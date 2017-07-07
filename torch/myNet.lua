require 'math'
require 'torch'
require 'nn'
require 'gnuplot'


dataLen = 5000000
testData = 1000
lr = 0.01

dataX = torch.rand(dataLen, 1) * 45
dataY = torch.rand(dataLen, 1)
preds = torch.Tensor(testData, 1)

dataY = dataX:clone():apply(function(x) return math.sin(x) * math.cos(x) end)

dataTestX =  torch.rand(testData, 1) * 35

-- create the network
require 'nn'
net = nn.Sequential()
module1 = nn.Linear(1, 50)
module2 = nn.Linear(50, 250)
module3 = nn.Linear(250, 150)
module4 = nn.Linear(150, 25)
module5 = nn.Linear(25, 1)

errorFunction = nn.MSECriterion()
errorFunction.sizeAverage = false
net:add(module1) net:add(nn.Tanh())
net:add(module2) net:add(nn.Tanh())
net:add(module3) net:add(nn.Tanh())
net:add(module4) net:add(nn.Tanh())
net:add(module5)


print("Training the net")
epochs = 5000
batchSize = 1000
for epoch=0,epochs,1 do

		print(string.format("Epoch %d", epoch))

	
		for j=1,batchSize,1 do
			index = math.min(torch.floor(torch.rand(1) * dataLen + 1)[1], dataLen)
			-- index = j
			pred = net:forward(dataX[index])
			err = errorFunction:forward(pred, dataY[index])
			-- if j == 1 then
			-- 	if err < 0.03 then epoch = epochs +1; break; end
			-- end
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
			-- {'Training set', dataX[{{1, 10000}}], dataY[{{1, 10000}}], '.'},
			 {'Test set', dataTestX:view(testData), preds:view(testData), '+'})
-- gnuplot.figure(2)
-- gnuplot.plot('Error in iteration', torch.Tensor(errorsX), torch.Tensor(errorsY), '.')