require 'torch'
require 'optim'
require 'gnuplot'

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

evaluations = {}
time = {}
timer = torch.Timer()
neval = 0
function JdJ(x)
	local Jx = J(x)
	neval = neval + 1
	table.insert(evaluations, Jx)
	table.insert(time, timer:time().real)
	return Jx, dJ(x)
end

state = {
	verbose = true,
	maxIter = 100
}

x0 = torch.rand(N)
cgx = x0:clone()
timer:reset()

-- run the model
optim.cg(JdJ, cgx, state)

-- turn the time table to a tensor
cgtime = torch.Tensor(time)
cgevaluations = torch.Tensor(evaluations)

-- plot the loss minimisation over time
-- gnuplot.figure(1)
-- gnuplot.title('CG loss minimisation over time')
-- gnuplot.plot(cgtime, cgevaluations)

-- add support for Stochastic Gradient Descent
evaluations = {}
time = {}
neval = 0
state = {
	lr = 0.1
}

-- clone the inputs
x = x0:clone()
timer:reset()

-- loop using SGD
for i =1, 1000 do
	optim.sgd(JdJ, x, state)
	table.insert(evaluations, Jx)
end

sgdtime = torch.Tensor(time)
sgdevaluations = torch.Tensor(evaluations)
-- gnuplot.figure(2)
-- gnuplot.title("SGD loss minimisation over time")
-- gnuplot.plot(sgdtime, sgdevaluations)

-- plot them together
gnuplot.pngfigure('plot.png')
gnuplot.plot(
	{'CG', cgtime, cgevaluations, '-'},
	{'SG', sgdtime, sgdevaluations, '-'})
gnuplot.xlabel('time [s]')
gnuplot.ylabel('J(x)')
gnuplot.plotflush()