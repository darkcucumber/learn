require 'nn'

n = 5 -- input dim
K = 3 -- output dim
lin = nn.Linear(n, K) -- go from x(size 5) -> h_Theta(x) (size 3)
print(lin)
Theta_1 = torch.cat(lin. bias, lin.weight, 2) -- concatenate (by dimension 2 - columns)
-- the bias and weights
-- this way we construct the matrix Theta_1 (first column are bias values, latter columns are weights)
-- gradWeight = dE / dW 
-- gradBias = dE / db
gradTheta_1 = torch.cat(lin.gradBias, lin.gradWeight, 2)
-- zero these parameters
lin:zeroGradParameters()
-- both input and output are currently empty

sig = nn.Sigmoid()
{sig} -- empty gradInput, empty output
require 'gnuplot'
z = torch.linspace(-10, 10, 2001)
gnuplot.plot(z, sig(z))

-- Forward pass --
x = torch.randn(n)
a1 = x
-- compute
h_Theta = sig:forward(lin:forward(x))

-- let us understand what happened behind the scenes
-- Theta_1 * a1 (a1 is equal to x)
z2 = Theta_1 * torch.cat(torch.ones(1), a1) -- [x0 = 1, x1, x2, ..., xn]
-- apply sigmoid by hand, first clone z2 (to not overwrite it), then apply a lambda
a2 = z2:clone():apply(function(z) return 1/(1 + math.exp(-z)) end)

-- Backward pass / back-propagation --
loss = nn.MSECriterion() -- has fields gradInput (tensor), output (single value) and sizeAverage
{loss} -- prints the fields
? nn.MSECriterion -- help
loss.sizeAverage = false -- don't compute average

y = torch.rand(K) -- 0 to 1

-- forward(input, target)
E = loss:forward(h_Theta, y) -- (h_Theta - y):pow(2):sum() czyli 1/2 * (suma po k) (yk - ak(L))
(h_Theta - y):pow(2):sum()

-- compute
dE_dh = loss:updateGradInput(h_Theta, y)
dE_dh

-- compute the same by hand
2 * (h_Theta - y)

-- lets compute error of layer 2
delta_2 = sig:updateGradInput(z2, dE_dh)
-- by hand
dE_dh:clone():cmul(a2):cmul(1 - a2)

-- lets compute the partial derivatiive of the model
lin:accGradParameters(x, delta_2)

-- let us see what happened
torch.cat(lin.gradBias, lin.gradWeight, 2) -- corresponds to part(E)/part(Theta_1)

-- lets verify if its correct

delta_2:view(-1, 1) * torch.cat(torch.ones(1), x, 1):view(1, -1) -- part(E)/part(Theta_1) = a1 * (delta_2):transpose()

-- next step
lin_gradInput = lin:updateGradInput(x, delta_2) -- corresponds to (Theta_l):t() * delta_l+1 inside delta_l = [(Theta_l):t() * delta_l+1]:cmul(z_l)
-- by hand
lin.weight:t() * delta_2

-- but we don't have to use the nn package this way...
-- it can be automated (thank Gods)
-- hide some intuition and gotchas

--- let us define a network
net = nn.Sequential() -- a sequential series of blocks
net:add(lin)
net:add(sig)
pred =  net:forward(x) -- lets compute h_Theta (the prediction)
err = loss:forward(pred, y) -- lets compute the error E
gradCriterion = loss:backward(pred, y) -- lets compute dE/dh
net:get(1) -- get first module within the network
torch.cat(net:get(1).gradBias, net:get(1).gradWeight, 2) -- obtain the grad weight 
-- zero the grad parameters
net:zeroGradParameters()
-- go backward
net:backward(x, gradCriterion) -- lin_gradInput
-- define learning rate
etha = 0.01
-- update the parameters based on the learning rate
net:updateParameters(etha)


-- so can we train a module?
