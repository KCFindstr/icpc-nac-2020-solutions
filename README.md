# 2020 ICPC North America Championship Solutions
Here are my solutions to [NAC 2020](http://nac.icpc.global/).

## Problem A - Another Coin Weighing Puzzle
Consider the decision tree. Suppose we get the sequence <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/3aecf84f0cba0bf1ddb37c2ba53bb0b7.svg" align=middle width=150.52324979999997pt height=24.65753399999998pt/> on weighings. Notice that only relative scale of the weights matter because we have no idea about the weight of fake coins, therefore we require <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/499f47b8473085dbe877f66caf2f829f.svg" align=middle width=136.72395989999998pt height=24.65753399999998pt/> to be <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/034d0a6be0424bffe9a6e7ac9236c0f5.svg" align=middle width=8.219209349999991pt height=21.18721440000001pt/> to avoid overcounting. The maximum number of leaves the decision tree could have equals to the number of valid sequences <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/53d147e7f3fe6e47ee05b88b166bd3f6.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> where each element of <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/53d147e7f3fe6e47ee05b88b166bd3f6.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> lies in the range <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/adaad998a08ff08eca83c73ad8d9390f.svg" align=middle width=47.37448979999999pt height=24.65753399999998pt/>. (Signs indicate whether left / right is heavier)

We can show that such decision tree exists, because a sequence <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/53d147e7f3fe6e47ee05b88b166bd3f6.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> could also map to the number of coins to put on the left / right side of the scale each time, for coins in a fixed bag. Therefore the answer is exactly the number of valid sequences <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/53d147e7f3fe6e47ee05b88b166bd3f6.svg" align=middle width=12.32879834999999pt height=22.465723500000017pt/> such that:
1. <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/73fd56d493e7ca2d7585e672ad599b9a.svg" align=middle width=166.8608007pt height=24.65753399999998pt/>
2. <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/082908fdd27a407db2f8f37c56542fd1.svg" align=middle width=114.67457759999998pt height=22.831056599999986pt/>

To compute this, we can use mobius function.
<p align="center"><img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/af7d0e5f28f54b2c682c12f557832b31.svg" align=middle width=1236.5811711pt height=59.03992379999999pt/></p>

*The extra <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/e0795d29372b8c5979fca89e51f78ac9.svg" align=middle width=57.53425259999999pt height=24.65753399999998pt/> comes from the special case when all <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/281a9a88b90811b031714ff94f5bd9b3.svg" align=middle width=47.93843504999999pt height=22.465723500000017pt/>. When deriving the formula, we don't consider this case in the summation.

Overall runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/431099fcf169d282080c0b7d41221af5.svg" align=middle width=76.00154924999998pt height=24.65753399999998pt/>.

## Problem B - Mini Battleship
Simulation and search. Prune branches wherever possible.

## Problem C - Bomas
Let's put queries offline and consider all queries circles together with existing circles.

The outlines of circles do not intersect, and thus the inclusion relationship of circles form a tree. We root the tree with the outside area. Compute and store the leftmost and rightmost border of circles, add an event of "Entering the circle" at the leftmost x-coordinate, and "Leaving the circle" at the rightmost x-coordinate. Sort and scan the events by x-coordinate, and maintain the upper and lower arc of the circle separately using an ordered set, because relative order of y-coordinates of arcs never change. We can know the parent of each circle by finding the arc right above it when we scan through its left border, and in this way constructs the tree structure.

The rest of the problem is just a classical DP problem - independent set on a tree.

Runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/c55f40a98d74d6754f146e5384773404.svg" align=middle width=72.2268393pt height=24.65753399999998pt/>.

## Problem D - All Kill
Let's begin with a solution that is not completely correct.

The problem can be interpreted as finding the number of ways that your friend comes up with the solution of each problem, such that all problems are solved in the end and your coding time is consecutive for each problem.

Since we know the number of minutes you're coding problems and the number of minutes you're idle, let's use a time slot for coding each problem and a time slot for each idle minute. Let <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/6508a59d3e4b549e4a88bf5fdd1961b5.svg" align=middle width=94.03914794999999pt height=26.438629799999987pt/>, then the number of total time slots is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/535ee047d64903d00b08962a9176a817.svg" align=middle width=71.85296909999998pt height=22.465723500000017pt/>. The problem becomes finding the number of ways to assign each problem a time slot.

Let's order the problems in ascending problem number. For the i-th problem, we can:
1. Assign an empty time slot. The number of ways to do this is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/725fb094bffd8f982873cd6a373e1a10.svg" align=middle width=138.70322069999997pt height=24.65753399999998pt/>.
2. Assign a problem to some time slots that is already occupied. In this case, the problem will be postponed to the next available slot. The number of ways to do this is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/88efe1bdf77fcfc10cb1c48caab7194b.svg" align=middle width=57.70751249999999pt height=31.75825949999999pt/>.

Therefore, we can consider each problem indenpendently, and the answer would be the product of the number of ways to assign each problem a slot.

Noticed the issue? In the second case, there may not be one available slot if all later time slots are occupied. To fix this issue, we consider the time slots in a loop, i.e. the next time slot of the last one is the first one. In this way, we can always find one available time slot after skipping occupied ones. We'll need to break the loop somewhere, therefore we add one more time slot for the break, and at the end we multiple the answer by the number of ways to break the loop using one empty time slot, i.e. <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/133a979ede95218cff1078ccda9ba795.svg" align=middle width=70.20530219999998pt height=22.465723500000017pt/>. Finally, we need to divide the answer by <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/0f530baca502bff42e76318f7cd0a594.svg" align=middle width=100.1633688pt height=22.465723500000017pt/> because we overcount rotations of the same loop.

Runtime: <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9af2fa2c4c62846463ef7db2a5956c57.svg" align=middle width=85.64759279999998pt height=24.65753399999998pt/>

## Problem E - Grid Guardian
Notice that if either n or m is odd, then we can only place obstacles on even indexes of that dimension. Use pigeonhole principle for a formal proof. So the problem can be solved easily in such cases.

Let's only consider the case where n and m are both even. We divide the grid into <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/7afe6068b04bc231516c722c67aa7dc8.svg" align=middle width=36.52961069999999pt height=21.18721440000001pt/> squares, and for each square we must put exactly one obstacle. For each row, there is some k (possibly 0) such that the leftmost k squares have an obstable on the right column of the square and the rest have an obstacle on the left. (If not, there would be an empty <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/7afe6068b04bc231516c722c67aa7dc8.svg" align=middle width=36.52961069999999pt height=21.18721440000001pt/> square across the boundary of two squares in this row) Same for columns.

However, this is a necessary but insufficient condition. There are two cases that violates the constraint:
```
.x ..
.. .x
x. ..
.. x.
```
```
.. x.
x. ..
.. .x
.x ..
```

To take this into account, we need to do a state compression dynamic programming. Let <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/6904110df720ca2b8f78c86405daeb90.svg" align=middle width=62.980584149999984pt height=24.65753399999998pt/> be the number of ways to construct a <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/a4f55be439b55a68ad1330e22e6fe097.svg" align=middle width=43.84050329999999pt height=21.68300969999999pt/> grid without <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/7afe6068b04bc231516c722c67aa7dc8.svg" align=middle width=36.52961069999999pt height=21.18721440000001pt/> empty squares, where the k value of the last column is k, and the last column has state S. S is a binary number which uses its j-th bit to indicate whether the last <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/7afe6068b04bc231516c722c67aa7dc8.svg" align=middle width=36.52961069999999pt height=21.18721440000001pt/> square on the j-th row has the obstacle on its left column. If that is true, all later squares must have their obstacles on the left columns. These states are sufficient for dynamic programming while eliminating the violation case.

I think this problem is supposed to be solved by state compression dynamic programming based on contour lines which should give a better time complexity, but I'm too lazy to write that solution so I tried to compute a transition table and optimize my DP with prefix sums. This solution passes the test cases within time limit.

## Problem F - Hopscotch 50
Let <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9ab9917650e3d8422cbfb90a920fae96.svg" align=middle width=43.28237429999999pt height=24.65753399999998pt/> be the minimum distance traveled ending at the tile <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/aa20264597f5a63b51587e0581c48f2c.svg" align=middle width=33.46496009999999pt height=24.65753399999998pt/>. We iterate over tiles in increasing order of their values and update DP values correspondingly.

Runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/4a083b18a8d541584fecf7c22fb90fa5.svg" align=middle width=43.02219404999999pt height=26.76175259999998pt/>.

## Problem G - ICPC Camp
Binary search on D. Then the problem becomes a decision problem - given D and s, is there a feasible selection of problems?

Sort the problems in ascending order of difficulties. Notice that for each classical problem, the range of creative problems that could be selected at the same time lie in a consecutive range. Therefore, the problem is equivalent to selecting maximum number of items so that each item matches a unique range. This requires a classical greedy algorithm.

Runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/64467e4490da359fb7e347be583a0ac5.svg" align=middle width=106.64454734999998pt height=24.65753399999998pt/>.

## Problem H - Letter Wheels
Compute all feasible offsets for each pair of rows. Once done, try all possible offsets of second and third rows, check if this results in a valid letter wheel using the preprocessed results. When calculating minimum rotation, also take rotating the first row into account.
Runtime: <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/3987120c67ed5a9162aa9841b531c3a9.svg" align=middle width=43.02219404999999pt height=26.76175259999998pt/>.

## Problem I - Editing Explosion
Let <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/ead3d02ae62fcecec7543efdd18aeecc.svg" align=middle width=46.59933794999999pt height=24.65753399999998pt/> denote the number of valid strings of length i, and S is a compressed state containing the edit distance from current string to the j-th prefix of the query string. i is upper bounded by |s|+d. Notice that the edit distance from current string to the 0-th prefix (length 0) is exactly i, and the edit distances to j-th and (j+1)-th predix differ by at most 1. Thus we could use a 3-based integer to encode the difference which allows us to retrieve the entire edit distance array.

The rest of the transition is very similar to finding edit distance between to strings.

The total runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/8146e78f58195a574cb62281c66910fa.svg" align=middle width=135.8149947pt height=29.190975000000005pt/>.

## Problem J - Lunchtime Name Recall
Let <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/ead3d02ae62fcecec7543efdd18aeecc.svg" align=middle width=46.59933794999999pt height=24.65753399999998pt/> be the maximum number of colleagues we can identify, given that on the i-th day, we can identify some groups of people encoded in S. Basically we can just do a brute force search on this since data range is small, but we need some optimizations:
1. We only need to know the size of each group in the state S. Thus we can sort groups in ascending order of group size and hash them.
2. When we try to distribute burgers to all groups we have, we need a recursive helper function. Since groups are already sorted, groups of equal sizes must be consecutive. For these groups, we force distributing no fewer burgers to prior groups to prune branches.

Runtime is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/c962a40ac63c9b7094a4dba35e689c0f.svg" align=middle width=78.67108589999998pt height=26.76175259999998pt/>, where <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/f010a0fda7cdcc04209d9381ef5fca27.svg" align=middle width=31.08266699999999pt height=24.65753399999998pt/> is the partition number of integer n. Note that this is a very loose bound.

## Problem K - Rooted Subtrees
For two roots r, p:
1. If either u or v is not on the path <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9568f2cc7e3b8760998aee45fa2d5bb1.svg" align=middle width=41.71412189999999pt height=14.15524440000002pt/>, then <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9f237b90e58fc3a0fa3b254ae62d2c36.svg" align=middle width=95.89374794999999pt height=24.65753399999998pt/> should be a subtree existing in both <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/78543ca0738739880432659c1a7f290d.svg" align=middle width=16.06363439999999pt height=22.465723500000017pt/> and <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/dab103ea81b430a6c3f72929005db4e9.svg" align=middle width=16.38266354999999pt height=22.465723500000017pt/>;
2. if both u and v are on the path <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9568f2cc7e3b8760998aee45fa2d5bb1.svg" align=middle width=41.71412189999999pt height=14.15524440000002pt/>, then <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9f237b90e58fc3a0fa3b254ae62d2c36.svg" align=middle width=95.89374794999999pt height=24.65753399999998pt/> would be a unique set as long as <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/6c4adbc36120d62b98deef2a20d5d303.svg" align=middle width=8.55786029999999pt height=14.15524440000002pt/> does not proceed <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/6dbb78540bd76da3f1625782d42d6d16.svg" align=middle width=9.41027339999999pt height=14.15524440000002pt/> on <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9568f2cc7e3b8760998aee45fa2d5bb1.svg" align=middle width=41.71412189999999pt height=14.15524440000002pt/>. Let the number of nodes on the path <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/9568f2cc7e3b8760998aee45fa2d5bb1.svg" align=middle width=41.71412189999999pt height=14.15524440000002pt/> be x (inclusively), then the number of ways to choose u,v is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/acbb965d918505ac9d7e162d7109d0a1.svg" align=middle width=41.826698099999994pt height=33.20539859999999pt/>.

Therefore, the answer is <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/a02c4a5df866a58c98626c3156352ce9.svg" align=middle width=103.24347659999998pt height=33.20539859999999pt/>. To compute the distance between two nodes on a tree, we need to know their LCA. There are a lot of ways to do this and I used Tarjan's offline algorithm.

Runtime: <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/2bc5b4a253fb9e315c33b6b7c4752dec.svg" align=middle width=68.87654234999998pt height=24.65753399999998pt/>

## Problem L - Tomb Raider
For each gargoyle, we can find the first gargoyle or obstacle to each of its 4 faces with memoization search. Then, the direction of this gargoyle uniquely defines the direction of all related gargoyles, and this process repeats recursively. In other words, for each connected component of gargoyles, we choose the direction of an anbitrary gargoyle, then the directions of all other gargoyles inside the same component can be determined. Therefore, there are only two ways to place the gargoyles inside the same connected component, and we can choose the one requiring fewer rotations. Do this for each connected component to get the answer.

Runtime: <img src="https://gitcdn.link/repo/KCFindstr/icpc-nac-2020-solutions/master/svgs/27bab83a05e94a7c15a396201e3dcd57.svg" align=middle width=50.080834649999986pt height=24.65753399999998pt/>.