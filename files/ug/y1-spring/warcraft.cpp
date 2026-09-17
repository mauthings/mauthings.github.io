/*
描述
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为1,2,3 .... N ( N <= 20 )。红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），则武士死亡（消失）。

有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。

武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。反击可能致敌人于死地。

如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。

如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。

城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。

当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。

各种武器有其特点：

sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.

arrow有一个攻击力值R。如果下一步要走到的城市有敌人，那么拥有arrow的武士就会放箭攻击下一个城市的敌人（不能攻击对方司令部里的敌人）而不被还击。arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。arrow使用3次后即被耗尽，武士失去arrow。两个相邻的武士可能同时放箭把对方射死。

拥有bomb的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，而且假设武士可以知道敌人的攻击力和生命值），那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。

武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

不同的武士有不同的特点。

dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有"士气"这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。士气增减发生在欢呼之前。

ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。

iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。

lion 有"忠诚度"这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓"战斗前"，就是每个小时的40分前的一瞬间。

wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。

以下是不同时间会发生的不同事件：

在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。

在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。

在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。

在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。

在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。

在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。

在每个小时的第40分：在有两个武士的城市，会发生战斗。 如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有"武士主动攻击"，"武士反击"，"武士战死"的事件发生，但战斗胜利后应该发生的事情都会发生。如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。

在每个小时的第50分，司令部报告它拥有的生命元数量。

在每个小时的第55分，每个武士报告其拥有的武器情况。

武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。

任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。

任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。

给定一个时间，要求你将从0点0分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：


1) 武士降生
输出样例： 000:00 blue lion 1 born

表示在 0点0分，编号为1的蓝魔lion武士降生
如果造出的是dragon，那么还要多输出一行，例：

000:00 blue dragon 1 born
Its morale is 23.34

表示该该dragon降生时士气是23. 34(四舍五入到小数点后两位)

如果造出的是lion，那么还要多输出一行，例:
000:00 blue lion 1 born
Its loyalty is 24

表示该lion降生时的忠诚度是24

2) lion逃跑
输出样例： 000:05 blue lion 1 ran away
表示在 0点5分，编号为1的蓝魔lion武士逃走

3) 武士前进到某一城市
输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
表示在 0点10分，红魔1号武士iceman前进到1号城市，此时他生命值为20,攻击力为30
对于iceman,输出的生命值和攻击力应该是变化后的数值

4)武士放箭
输出样例： 000:35 blue dragon 1 shot
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
000:35 blue dragon 1 shot and killed red lion 4
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。

5)武士使用bomb
输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。

6) 武士主动进攻
输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
表示在0点40分，1号城市中，红魔1号武士iceman 进攻蓝魔1号武士lion,在发起进攻前，红魔1号武士iceman生命值为20，攻击力为 30

7) 武士反击
输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1
表示在1点40分，1号城市中，蓝魔2号武士dragon反击红魔2号武士lion

8) 武士战死
输出样例：001:40 red lion 2 was killed in city 1
被箭射死的武士就不会有这一条输出。

9) 武士欢呼
输出样例：003:40 blue dragon 2 yelled in city 4

10) 武士获取生命元( elements )
输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter

输出不包括在30分不是通过战斗获取的elements

11) 旗帜升起
输出样例：004:40 blue flag raised in city 4

12) 武士抵达敌军司令部
输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
(此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值

13) 司令部被占领
输出样例：003:10 blue headquarter was taken

14)司令部报告生命元数量
000:50 100 elements in red headquarter
000:50 120 elements in blue headquarter
表示在0点50分，红方司令部有100个生命元，蓝方有120个

15)武士报告武器情况
000:55 blue wolf 2 has arrow(2),bomb,sword(23)
000:55 blue wolf 4 has no weapon
000:55 blue wolf 5 has sword(20)
表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。
蓝魔4号武士wolf没武器。
蓝魔5号武士wolf有一支攻击力为20的sword。
交代武器情况时，次序依次是：arrow,bomb,sword。如果没有某种武器，某种武器就不用提。报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。

在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些事件，序号小的应该先输出。

两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。

显然，13号事件发生之前的一瞬间一定发生了12号事件。输出时，这两件事算同一时间发生，但是应先输出12号事件

虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

输入
第一行是t,代表测试数据组数
每组样例共三行。
第一行，五个整数 M,N,R,K, T。其含义为：

每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000

输出
对每组数据，先输出一行：
Case n:
如对第一组数据就输出 Case1:
然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是"时: 分"，"时"有三位，"分"有两位。

样例输入
1
20 1 10 10 1000
20 20 30 10 20
5 5 5 5 5
样例输出
Case 1:
000:00 blue lion 1 born
Its loyalty is 10
000:10 blue lion 1 marched to city 1 with 10 elements and force 5
000:30 blue lion 1 earned 10 elements for his headquarter
000:50 20 elements in red headquarter
000:50 20 elements in blue headquarter
000:55 blue lion 1 has no weapon
001:00 blue dragon 2 born
Its morale is 0.00
001:10 blue lion 1 reached red headquarter with 10 elements and force 5
001:10 blue dragon 2 marched to city 1 with 20 elements and force 5
001:30 blue dragon 2 earned 10 elements for his headquarter
001:50 20 elements in red headquarter
001:50 10 elements in blue headquarter
001:55 blue lion 1 has no weapon
001:55 blue dragon 2 has arrow(3)
002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
002:10 red headquarter was taken
*/

/*
描述
魔兽世界的西面是红魔军的司令部，东面是蓝魔军的司令部。两个司令部之间是依次排列的若干城市，城市从西向东依次编号为1,2,3 .... N ( N <= 20 )。红魔军的司令部算作编号为0的城市，蓝魔军的司令部算作编号为N+1的城市。司令部有生命元，用于制造武士。

两军的司令部都会制造武士。武士一共有 dragon 、ninja、iceman、lion、wolf 五种。每种武士都有编号、生命值、攻击力这三种属性。

双方的武士编号都是从1开始计算。红方制造出来的第 n 个武士，编号就是n。同样，蓝方制造出来的第 n 个武士，编号也是n。

武士在刚降生的时候有一个初始的生命值，生命值在战斗中会发生变化，如果生命值减少到0（生命值变为负数时应当做变为0处理），则武士死亡（消失）。

有的武士可以拥有武器。武器有三种，sword, bomb,和arrow，编号分别为0,1,2。

武士降生后就朝对方司令部走，在经过的城市如果遇到敌人（同一时刻每个城市最多只可能有1个蓝武士和一个红武士），就会发生战斗。每次战斗只有一方发起主动进攻一次。被攻击者生命值会减去进攻者的攻击力值和进攻者手中sword的攻击力值。被进攻者若没死，就会发起反击，被反击者的生命值要减去反击者攻击力值的一半(去尾取整)和反击者手中sword的攻击力值。反击可能致敌人于死地。

如果武士在战斗中杀死敌人（不论是主动进攻杀死还是反击杀死），则其司令部会立即向其发送8个生命元作为奖励，使其生命值增加8。当然前提是司令部得有8个生命元。如果司令部的生命元不足以奖励所有的武士，则优先奖励距离敌方司令部近的武士。

如果某武士在某城市的战斗中杀死了敌人，则该武士的司令部立即取得该城市中所有的生命元。注意，司令部总是先完成全部奖励工作，然后才开始从各个打了胜仗的城市回收生命元。对于因司令部生命元不足而领不到奖励的武士，司令部也不会在取得战利品生命元后为其补发奖励。

如果一次战斗的结果是双方都幸存(平局)，则双方都不能拿走发生战斗的城市的生命元。

城市可以插旗子，一开始所有城市都没有旗子。在插红旗的城市，以及编号为奇数的无旗城市，由红武士主动发起进攻。在插蓝旗的城市，以及编号为偶数的无旗城市，由蓝武士主动发起进攻。

当某个城市有连续两场战斗都是同一方的武士杀死敌人(两场战斗之间如果有若干个战斗时刻并没有发生战斗，则这两场战斗仍然算是连续的；但如果中间有平局的战斗，就不算连续了) ，那么该城市就会插上胜方的旗帜，若原来插着败方的旗帜，则败方旗帜落下。旗帜一旦插上，就一直插着，直到被敌人更换。一个城市最多只能插一面旗帜，旗帜没被敌人更换前，也不会再次插同颜色的旗。

各种武器有其特点：

sword武器的初始攻击力为拥有它的武士的攻击力的20%（去尾取整）。但是sword每经过一次战斗(不论是主动攻击还是反击)，就会变钝，攻击力变为本次战斗前的80% (去尾取整)。sword攻击力变为0时，视为武士失去了sword。如果武士降生时得到了一个初始攻击力为0的sword，则视为武士没有sword.

arrow有一个攻击力值R。如果下一步要走到的城市有敌人，那么拥有arrow的武士就会放箭攻击下一个城市的敌人（不能攻击对方司令部里的敌人）而不被还击。arrow使敌人的生命值减少R，若减至小于等于0，则敌人被杀死。arrow使用3次后即被耗尽，武士失去arrow。两个相邻的武士可能同时放箭把对方射死。

拥有bomb的武士，在战斗开始前如果判断自己将被杀死（不论主动攻击敌人，或者被敌人主动攻击都可能导致自己被杀死，而且假设武士可以知道敌人的攻击力和生命值），那么就会使用bomb和敌人同归于尽。武士不预测对方是否会使用bomb。

武士使用bomb和敌人同归于尽的情况下，不算是一场战斗，双方都不能拿走城市的生命元，也不影响城市的旗帜。

不同的武士有不同的特点。

dragon可以拥有一件武器。编号为n的dragon降生时即获得编号为 n%3 的武器。dragon还有"士气"这个属性，是个浮点数，其值为它降生后其司令部剩余生命元的数量除以造dragon所需的生命元数量。dragon 在一次在它主动进攻的战斗结束后，如果还没有战死，而且士气值大于0.8，就会欢呼。dragon每取得一次战斗的胜利(敌人被杀死)，士气就会增加0.2，每经历一次未能获胜的战斗，士气值就会减少0.2。士气增减发生在欢呼之前。

ninja可以拥有两件武器。编号为n的ninja降生时即获得编号为 n%3 和 (n+1)%3的武器。ninja 挨打了也从不反击敌人。

iceman有一件武器。编号为n的iceman降生时即获得编号为 n%3 的武器。iceman 每前进两步，在第2步完成的时候，生命值会减少9，攻击力会增加20。但是若生命值减9后会小于等于0，则生命值不减9,而是变为1。即iceman不会因走多了而死。

lion 有"忠诚度"这个属性，其初始值等于它降生之后其司令部剩余生命元的数目。每经过一场未能杀死敌人的战斗，忠诚度就降低K。忠诚度降至0或0以下，则该lion逃离战场,永远消失。但是已经到达敌人司令部的lion不会逃跑。Lion在己方司令部可能逃跑。lion 若是战死，则其战斗前的生命值就会转移到对手身上。所谓"战斗前"，就是每个小时的40分前的一瞬间。

wolf降生时没有武器，但是在战斗中如果获胜（杀死敌人），就会缴获敌人的武器，但自己已有的武器就不缴获了。被缴获的武器当然不能算新的，已经被用到什么样了，就是什么样的。

以下是不同时间会发生的不同事件：

在每个整点，即每个小时的第0分， 双方的司令部中各有一个武士降生。

红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。

蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。

制造武士需要生命元。

制造一个初始生命值为 m 的武士，司令部中的生命元就要减少 m 个。

如果司令部中的生命元不足以制造某武士，那么司令部就等待，直到获得足够生命元后的第一个整点，才制造该武士。例如，在2:00，红方司令部本该制造一个 wolf ，如果此时生命元不足，那么就会等待，直到生命元足够后的下一个整点，才制造一个 wolf。

在每个小时的第5分，该逃跑的lion就在这一时刻逃跑了。

在每个小时的第10分：所有的武士朝敌人司令部方向前进一步。即从己方司令部走到相邻城市，或从一个城市走到下一个城市。或从和敌军司令部相邻的城市到达敌军司令部。

在每个小时的第20分：每个城市产出10个生命元。生命元留在城市，直到被武士取走。

在每个小时的第30分：如果某个城市中只有一个武士，那么该武士取走该城市中的所有生命元，并立即将这些生命元传送到其所属的司令部。

在每个小时的第35分，拥有arrow的武士放箭，对敌人造成伤害。放箭事件应算发生在箭发出的城市。注意，放箭不算是战斗，因此放箭的武士不会得到任何好处。武士在没有敌人的城市被箭射死也不影响其所在城市的旗帜更换情况。

在每个小时的第38分，拥有bomb的武士评估是否应该使用bomb。如果是，就用bomb和敌人同归于尽。

在每个小时的第40分：在有两个武士的城市，会发生战斗。 如果敌人在5分钟前已经被飞来的arrow射死，那么仍然视为发生了一场战斗，而且存活者视为获得了战斗的胜利。此情况下不会有"武士主动攻击"，"武士反击"，"武士战死"的事件发生，但战斗胜利后应该发生的事情都会发生。如Wolf一样能缴获武器，旗帜也可能更换，等等。在此情况下,Dragon同样会通过判断是否应该轮到自己主动攻击来决定是否欢呼。

在每个小时的第50分，司令部报告它拥有的生命元数量。

在每个小时的第55分，每个武士报告其拥有的武器情况。

武士到达对方司令部后就算完成任务了，从此就呆在那里无所事事。

任何一方的司令部里若是出现了2个敌人，则认为该司令部已被敌人占领。

任何一方的司令部被敌人占领，则战争结束。战争结束之后就不会发生任何事情了。

给定一个时间，要求你将从0点0分开始到此时间为止的所有事件按顺序输出。事件及其对应的输出样例如下：


1) 武士降生
输出样例： 000:00 blue lion 1 born

表示在 0点0分，编号为1的蓝魔lion武士降生
如果造出的是dragon，那么还要多输出一行，例：

000:00 blue dragon 1 born
Its morale is 23.34

表示该该dragon降生时士气是23. 34(四舍五入到小数点后两位)

如果造出的是lion，那么还要多输出一行，例:
000:00 blue lion 1 born
Its loyalty is 24

表示该lion降生时的忠诚度是24

2) lion逃跑
输出样例： 000:05 blue lion 1 ran away
表示在 0点5分，编号为1的蓝魔lion武士逃走

3) 武士前进到某一城市
输出样例： 000:10 red iceman 1 marched to city 1 with 20 elements and force 30
表示在 0点10分，红魔1号武士iceman前进到1号城市，此时他生命值为20,攻击力为30
对于iceman,输出的生命值和攻击力应该是变化后的数值

4)武士放箭
输出样例： 000:35 blue dragon 1 shot
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭。如果射出的箭杀死了敌人，则应如下输出：
000:35 blue dragon 1 shot and killed red lion 4
表示在 0点35分，编号为1的蓝魔dragon武士射出一支箭，杀死了编号为4的红魔lion。

5)武士使用bomb
输出样例： 000:38 blue dragon 1 used a bomb and killed red lion 7
表示在 0点38分，编号为1的蓝魔dragon武士用炸弹和编号为7的红魔lion同归于尽。

6) 武士主动进攻
输出样例：000:40 red iceman 1 attacked blue lion 1 in city 1 with 20 elements and force 30
表示在0点40分，1号城市中，红魔1号武士iceman 进攻蓝魔1号武士lion,在发起进攻前，红魔1号武士iceman生命值为20，攻击力为 30

7) 武士反击
输出样例：001:40 blue dragon 2 fought back against red lion 2 in city 1
表示在1点40分，1号城市中，蓝魔2号武士dragon反击红魔2号武士lion

8) 武士战死
输出样例：001:40 red lion 2 was killed in city 1
被箭射死的武士就不会有这一条输出。

9) 武士欢呼
输出样例：003:40 blue dragon 2 yelled in city 4

10) 武士获取生命元( elements )
输出样例：001:40 blue dragon 2 earned 10 elements for his headquarter

输出不包括在30分不是通过战斗获取的elements

11) 旗帜升起
输出样例：004:40 blue flag raised in city 4

12) 武士抵达敌军司令部
输出样例：001:10 red iceman 1 reached blue headquarter with 20 elements and force 30
(此时他生命值为20,攻击力为30）对于iceman,输出的生命值和攻击力应该是变化后的数值

13) 司令部被占领
输出样例：003:10 blue headquarter was taken

14)司令部报告生命元数量
000:50 100 elements in red headquarter
000:50 120 elements in blue headquarter
表示在0点50分，红方司令部有100个生命元，蓝方有120个

15)武士报告武器情况
000:55 blue wolf 2 has arrow(2),bomb,sword(23)
000:55 blue wolf 4 has no weapon
000:55 blue wolf 5 has sword(20)
表示在0点55分，蓝魔2号武士wolf有一支arrow（这支arrow还可以用2次），一个bomb，还有一支攻击力为23的sword。
蓝魔4号武士wolf没武器。
蓝魔5号武士wolf有一支攻击力为20的sword。
交代武器情况时，次序依次是：arrow,bomb,sword。如果没有某种武器，某种武器就不用提。报告时，先按从西向东的顺序所有的红武士报告，然后再从西向东所有的蓝武士报告。

输出事件时：

首先按时间顺序输出；

同一时间发生的事件，按发生地点从西向东依次输出. 武士前进的事件, 算是发生在目的地。

在一次战斗中有可能发生上面的 6 至 11 号事件。这些事件都算同时发生，其时间就是战斗开始时间。一次战斗中的这些事件，序号小的应该先输出。

两个武士同时抵达同一城市，则先输出红武士的前进事件，后输出蓝武士的。

显然，13号事件发生之前的一瞬间一定发生了12号事件。输出时，这两件事算同一时间发生，但是应先输出12号事件

虽然任何一方的司令部被占领之后，就不会有任何事情发生了。但和司令部被占领同时发生的事件，全都要输出。

输入
第一行是t,代表测试数据组数
每组样例共三行。
第一行，五个整数 M,N,R,K, T。其含义为：

每个司令部一开始都有M个生命元( 1 <= M <= 10000)
两个司令部之间一共有N个城市( 1 <= N <= 20 )
arrow的攻击力是R
lion每经过一场未能杀死敌人的战斗，忠诚度就降低K。
要求输出从0时0分开始，到时间T为止(包括T) 的所有事件。T以分钟为单位，0 <= T <= 5000

第二行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的初始生命值。它们都大于0小于等于10000

第三行：五个整数，依次是 dragon 、ninja、iceman、lion、wolf 的攻击力。它们都大于0小于等于10000

输出
对每组数据，先输出一行：
Case n:
如对第一组数据就输出 Case1:
然后按恰当的顺序和格式输出到时间T为止发生的所有事件。每个事件都以事件发生的时间开头，时间格式是"时: 分"，"时"有三位，"分"有两位。

样例输入
1
20 1 10 10 1000
20 20 30 10 20
5 5 5 5 5
样例输出
Case 1:
000:00 blue lion 1 born
Its loyalty is 10
000:10 blue lion 1 marched to city 1 with 10 elements and force 5
000:30 blue lion 1 earned 10 elements for his headquarter
000:50 20 elements in red headquarter
000:50 20 elements in blue headquarter
000:55 blue lion 1 has no weapon
001:00 blue dragon 2 born
Its morale is 0.00
001:10 blue lion 1 reached red headquarter with 10 elements and force 5
001:10 blue dragon 2 marched to city 1 with 20 elements and force 5
001:30 blue dragon 2 earned 10 elements for his headquarter
001:50 20 elements in red headquarter
001:50 10 elements in blue headquarter
001:55 blue lion 1 has no weapon
001:55 blue dragon 2 has arrow(3)
002:10 blue dragon 2 reached red headquarter with 20 elements and force 5
002:10 red headquarter was taken
*/


// 助教/老师好，这是重新整理过注释的最终版本
// 您审阅辛苦了

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

// ---- 全局常量：阵营 & 兵种 ----
char camp_name[2][5] = {"red", "blue"};     // 0是红方，1是蓝方
char type_name[5][7] = {"dragon", "ninja", "iceman", "lion", "wolf"}; // 五种武士的名字

// 两边造兵顺序
int red_order[]  = {0, 2, 3, 4, 1};  // 红方：iceman→lion→wolf→ninja→dragon
int blue_order[] = {4, 3, 0, 1, 2};  // 蓝方：lion→dragon→ninja→iceman→wolf



int M, N, R, K, T;
int cur_time;                      // 当前推进到的分钟数，驱动整个事件循环
int game_over;                     // 0=继续，1=某方司令部沦陷，收工
int init_hp[5], init_atk[5];       // 五种武士的基础生命值和攻击力

class City;  // 前置声明，武士类里要用到城市指针

// ========== 武士基类 ==========
// 所有武士共有的属性（生命、攻击、武器、位置）和行为都在这里
class Warrior {
public:
    int type;           // 0-dragon, 1-ninja, 2-iceman, 3-lion, 4-wolf
    int camp;           // 0-红方, 1-蓝方
    int id;             // 武士编号
    int hp, atk;        // 生命值、攻击力
    int sword, bomb, arrow;  // sword攻击力, bomb有/无, arrow剩余次数
    int pos;            // 所在城市编号

    Warrior(int _type, int _camp, int _id) {
        type = _type; camp = _camp; id = _id;
        hp = init_hp[type];
        atk = init_atk[type];
        sword = bomb = arrow = 0;

        // 武器分配：dragon/iceman 拿 n%3, ninja 拿两件, lion/wolf 赤手空拳
        if (type == 0) {          // dragon: 按 n%3 选一件武器
            if (id % 3 == 0) sword = atk / 5;
            else if (id % 3 == 1) bomb = 1;
            else arrow = 3;
        } else if (type == 1) {   // ninja: 两件武器，n%3 和 (n+1)%3
            if (id % 3 == 0) sword = atk / 5;
            else if (id % 3 == 1) bomb = 1;
            else arrow = 3;
            if ((id + 1) % 3 == 0) sword = atk / 5;
            else if ((id + 1) % 3 == 1) bomb = 1;
            else arrow = 3;
        } else if (type == 2) {   // iceman: 同 dragon，一件武器
            if (id % 3 == 0) sword = atk / 5;
            else if (id % 3 == 1) bomb = 1;
            else arrow = 3;
        }
        // lion 和 wolf 天生没有武器，靠实力和捡漏

        // 初始位置：红方老家=0号城市，蓝方老家=N+1号城市
        if (camp == 0) pos = 0;
        else pos = N + 1;
    }

    bool is_alive() { return hp > 0; }

    virtual bool will_runaway() { return false; }  // 默认不跑，只有lion会重写

    // 朝敌方司令部走一格（红向东pos++，蓝向西pos--）
    virtual void move_unit() {
        if (camp == 0) pos++;
        else pos--;
    }

    // 放箭，箭射向相邻城市的敌人，扣R点血
    void shoot_arrow(Warrior* enemy) {
        if (arrow == 0) return;  // 没箭不射
        enemy->hp -= R;
        arrow--;
        if (enemy->hp <= 0)
            printf("%03d:35 %s %s %d shot and killed %s %s %d\n",
                cur_time / 60, camp_name[camp], type_name[type], id,
                camp_name[enemy->camp], type_name[enemy->type], enemy->id);
        else
            printf("%03d:35 %s %s %d shot\n",
                cur_time / 60, camp_name[camp], type_name[type], id);
    }

    // 自爆
    void use_bomb(Warrior* enemy) {
        if (bomb == 0) return;
        printf("%03d:38 %s %s %d used a bomb and killed %s %s %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id,
            camp_name[enemy->camp], type_name[enemy->type], enemy->id);
        hp = 0; enemy->hp = 0;  // 同归于尽
    }

    // 55分时向司令部汇报自己身上的装备
    void report_weapon() {
        printf("%03d:55 %s %s %d has ", cur_time / 60, camp_name[camp], type_name[type], id);
        if (sword == 0 && bomb == 0 && arrow == 0) {
            printf("no weapon");  // 穷光蛋
        }
        int comma = 0;
        // 顺序 arrow → bomb → sword
        if (arrow) { printf("%sarrow(%d)", comma ? "," : "", arrow); comma = 1; }
        if (bomb)  { printf("%sbomb", comma ? "," : ""); comma = 1; }
        if (sword) { printf("%ssword(%d)", comma ? "," : "", sword); comma = 1; }
        printf("\n");
    }

    // 战死的时候喊一句
    void report_death() {
        printf("%03d:40 %s %s %d was killed in city %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id, pos);
    }

    // 反击 伤害 = atk/2 + sword攻击力。ninja会重写成空函数。
    virtual void fight_back(Warrior* enemy) {
        printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id,
            camp_name[enemy->camp], type_name[enemy->type], enemy->id, pos);
        enemy->hp -= atk / 2 + sword;
        if (enemy->hp <= 0) {
            if (enemy->type == 3)  // lion的战前血量归
                hp += enemy->hp + atk / 2 + sword;
            enemy->report_death();
        }
        sword = sword * 4 / 5;  // sword砍人就会变钝
    }

    // 伤害 = atk + sword攻击力。对方没死的话会被反击。
    virtual void attack_enemy(Warrior* enemy) {
        printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id,
            camp_name[enemy->camp], type_name[enemy->type], enemy->id, pos, hp, atk);
        enemy->hp -= atk + sword;
        if (enemy->hp <= 0) {
            if (enemy->type == 3)  // lion死了就把血量转给我
                hp += enemy->hp + atk + sword;
            enemy->report_death();
        } else {
            enemy->fight_back(this);  
        }
        sword = sword * 4 / 5;  // 刀砍完又变钝
    }

    virtual void yell(int win, int output) {}        // dragon专属：欢呼
    virtual void steal_weapon(Warrior* enemy) {}     // wolf专属：缴获武器
    void earn_elements();  // 战斗获胜后搜刮城市的生命元
};

// ========== 城市类 ==========
// 兼做司令部（city[0]=红HQ，city[N+1]=蓝HQ，city[1..N]=普通城市）
class City {
public:
    Warrior* warriors[2];  // [0]=红武士, [1]=蓝武士，同一个城市最多各一个
    int elements;          // 城里的生命元存量
    int flag;              // -1=无旗, 0=红旗, 1=蓝旗
    int last_win;          // 上一场战斗谁赢了（-1=平局或者还没打过）
    int born_cnt;          // 司令部用：已造武士总数（也是最新武士编号）
    int reach_cnt;         // 司令部用：敌军闯入人数
    int last_reach_id;     // 司令部用：上次抵达者的ID，防止重复输出
    int city_id;           // 城市编号，0~N+1

    City(int _id = 0) {
        warriors[0] = warriors[1] = NULL;
        elements = 0;
        flag = -1;
        last_win = -1;
        born_cnt = 0;
        reach_cnt = 0;
        last_reach_id = 0;
        city_id = _id;
    }

    // 根据旗帜和城市编号决定本次战斗谁先手：
    //   - 没旗：奇数城红先，偶数城蓝先
    //   - 有旗：旗帜颜色决定（红旗→0红先，蓝旗→1蓝先）
    int first_attacker() {
        if (flag == -1)
            return city_id % 2 == 0 ? 1 : 0;
        else
            return flag;
    }

    // 维护城头的旗帜：连续两场同一方胜利就升旗/换旗，平局打断计数
    void update_flag(int winner) {
        if (winner == -1) {          // 平局：连胜中断，重新开始数
            last_win = -1;
        } else {
            if (last_win == winner) {       // 连着赢了，可以升旗
                if (winner != flag) {       // 如果旗已经是自家的就不用再升
                    printf("%03d:40 %s flag raised in city %d\n",
                        cur_time / 60, camp_name[winner], city_id);
                    flag = winner;
                }
            } else {
                last_win = winner;           // 第一次赢
            }
        }
    }
};

City city[25]; 

// 战斗获胜后：把所在城市的生命元搬回己方司令部（只算40分战斗获取，30分的不走这里）
void Warrior::earn_elements() {
    printf("%03d:40 %s %s %d earned %d elements for his headquarter\n",
        cur_time / 60, camp_name[camp], type_name[type], id, city[pos].elements);

    city[camp * (N + 1)].elements += city[pos].elements;
    city[pos].elements = 0;
}

// ========== Dragon 武士 ==========
// 特点：一件武器(n%3)，有士气值，打赢+0.2打输-0.2，士气>0.8且主动攻击后欢呼
class Dragon : public Warrior {
public:
    double morale;

    Dragon(int _camp, int _id) : Warrior(0, _camp, _id) {
        // 士气 = 生完后司令部剩的钱 / 生dragon花的钱（浮点数）
        if (camp == 0) morale = (double)(city[0].elements - hp) / hp;
        else morale = (double)(city[N + 1].elements - hp) / hp;
        printf("%03d:00 %s dragon %d born\n", cur_time / 60, camp_name[camp], id);
        printf("Its morale is %.2lf\n", morale);
    }

    void yell(int win, int output) override {
        if (win) morale += 0.2;
        else morale -= 0.2;
        // 只有主动进攻方才能欢呼（output=1），注意浮点数比较加了个小epsilon
        if (output) if (morale > 0.8 + 1e-8)
            printf("%03d:40 %s %s %d yelled in city %d\n",
                cur_time / 60, camp_name[camp], type_name[type], id, pos);
    }
};

// ========== Ninja 武士 ==========
// 开局两件武器，但挨打不还手（我面对期末和调代码就这样）
class Ninja : public Warrior {
public:
    Ninja(int _camp, int _id) : Warrior(1, _camp, _id) {
        printf("%03d:00 %s ninja %d born\n", cur_time / 60, camp_name[camp], id);
    }
    void fight_back(Warrior* enemy) override {} 
};

// ========== Iceman 武士 ==========
// 一件武器，每走两步 hp-9(atk+20)，但不会自己死（hp最低维持1）
class Iceman : public Warrior {
public:
    int move_cnt;  

    Iceman(int _camp, int _id) : Warrior(2, _camp, _id) {
        move_cnt = 0;
        printf("%03d:00 %s iceman %d born\n", cur_time / 60, camp_name[camp], id);
    }

    void move_unit() override {
        if (camp == 0) pos++;
        else pos--;
        move_cnt++;
        // 每两步触发一次冰人特有的进化：变脆但变强
        if (move_cnt == 2) {
            move_cnt = 0;
            hp = max(hp - 9, 1);
            atk += 20;
        }
    }
};

// ========== Lion 武士 ==========
// 特：有忠诚度，不杀敌会掉忠诚，忠诚掉光就逃跑；战死的话血量送给对手
class Lion : public Warrior {
public:
    int loyalty;

    Lion(int _camp, int _id) : Warrior(3, _camp, _id) {
        // 忠诚度一开始等于生完后司令部剩下的
        if (camp == 0) loyalty = (double)city[0].elements - hp;
        else loyalty = (double)city[N + 1].elements - hp;
        printf("%03d:00 %s lion %d born\n", cur_time / 60, camp_name[camp], id);
        printf("Its loyalty is %d\n", loyalty);
    }

    bool will_runaway() override {
        // 已经杀到敌人司令部的lion不会跑
        if (pos == (1 - camp) * (N + 1)) return false;
        return loyalty <= 0;  // 忠诚没了就溜
    }

    void fight_back(Warrior* enemy) override {
        printf("%03d:40 %s %s %d fought back against %s %s %d in city %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id,
            camp_name[enemy->camp], type_name[enemy->type], enemy->id, pos);
        enemy->hp -= atk / 2 + sword;
        if (enemy->hp <= 0) {
            if (enemy->type == 3)
                hp += enemy->hp + atk / 2 + sword;
            enemy->report_death();
        } else {
            loyalty -= K;  // 对不起输了（）所以想跑了
        }
        sword = sword * 4 / 5;
    }

    void attack_enemy(Warrior* enemy) override {
        printf("%03d:40 %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
            cur_time / 60, camp_name[camp], type_name[type], id,
            camp_name[enemy->camp], type_name[enemy->type], enemy->id, pos, hp, atk);
        enemy->hp -= atk + sword;
        if (enemy->hp <= 0) {
            if (enemy->type == 3)
                hp += enemy->hp + atk + sword;
            enemy->report_death();
        } else {
            loyalty -= K;
            enemy->fight_back(this);
        }
        sword = sword * 4 / 5;
    }
};

// ========== Wolf 武士 ==========
// 特点：没有初始武器，但打赢了会把对方的武器扒过来（只要自己没有的）
class Wolf : public Warrior {
public:
    Wolf(int _camp, int _id) : Warrior(4, _camp, _id) {
        printf("%03d:00 %s wolf %d born\n", cur_time / 60, camp_name[camp], id);
    }

    void steal_weapon(Warrior* enemy) override {

        if (!sword) sword = enemy->sword;
        if (!bomb)  bomb  = enemy->bomb;
        if (!arrow) arrow = enemy->arrow;
    }
};

// ---- 预判战斗结果（给bomb判断用） ----
// p 是进攻方，q 是防守方；返回 {p会不会死, q会不会死}
pair<int, int> simulate_fight(Warrior* p, Warrior* q) {

    if (q->hp <= p->atk + p->sword) return {0, 1};
    // q如果还活着且不是ninja，反击能打死p吗
    if (q->type != 1 && p->hp <= q->atk / 2 + q->sword) return {1, 0};
    return {0, 0};  
}

// ========== 以下是事件处理函数，按游戏时间线排列 ==========
void born() {
    //// 红方降生
    if (city[0].elements >= init_hp[red_order[(city[0].born_cnt + 1) % 5]]) {
        int born_type = red_order[(city[0].born_cnt + 1) % 5];
        if (born_type == 0)      city[0].warriors[0] = new Dragon(0, ++city[0].born_cnt);
        else if (born_type == 1) city[0].warriors[0] = new Ninja(0, ++city[0].born_cnt);
        else if (born_type == 2) city[0].warriors[0] = new Iceman(0, ++city[0].born_cnt);
        else if (born_type == 3) city[0].warriors[0] = new Lion(0, ++city[0].born_cnt);
        else if (born_type == 4) city[0].warriors[0] = new Wolf(0, ++city[0].born_cnt);
        city[0].elements -= city[0].warriors[0]->hp;
    }
    //// 蓝方降生
    if (city[N + 1].elements >= init_hp[blue_order[(city[N + 1].born_cnt + 1) % 5]]) {
        int born_type = blue_order[(city[N + 1].born_cnt + 1) % 5];
        if (born_type == 0)      city[N + 1].warriors[1] = new Dragon(1, ++city[N + 1].born_cnt);
        else if (born_type == 1) city[N + 1].warriors[1] = new Ninja(1, ++city[N + 1].born_cnt);
        else if (born_type == 2) city[N + 1].warriors[1] = new Iceman(1, ++city[N + 1].born_cnt);
        else if (born_type == 3) city[N + 1].warriors[1] = new Lion(1, ++city[N + 1].born_cnt);
        else if (born_type == 4) city[N + 1].warriors[1] = new Wolf(1, ++city[N + 1].born_cnt);
        city[N + 1].elements -= city[N + 1].warriors[1]->hp;
    }
}

//// 05分: lion逃跑
void runaway() {
    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j < 2; j++) {
            if (city[i].warriors[j] != NULL && city[i].warriors[j]->will_runaway()) {
                printf("%03d:05 %s lion %d ran away\n",
                    cur_time / 60, camp_name[j], city[i].warriors[j]->id);
                city[i].warriors[j] = NULL;
            }
        }
    }
}

//// 10分: 武士前进
void move_all() {
    //// 红方从西向东, 逆向遍历避免覆盖
    for (int i = N; i >= 0; i--)
        if (city[i].warriors[0] != NULL) {
            city[i + 1].warriors[0] = city[i].warriors[0];
            city[i].warriors[0] = NULL;
            city[i + 1].warriors[0]->move_unit();
        }
    //// 蓝方从东向西
    for (int i = 1; i <= N + 1; i++)
        if (city[i].warriors[1] != NULL) {
            city[i - 1].warriors[1] = city[i].warriors[1];
            city[i].warriors[1] = NULL;
            city[i - 1].warriors[1]->move_unit();
        }

    //// 蓝武士到达红司令部的检测
    if (city[0].warriors[1] != NULL) {
        if (city[0].last_reach_id != city[0].warriors[1]->id) {
            printf("%03d:10 blue %s %d reached red headquarter with %d elements and force %d\n",
                cur_time / 60, type_name[city[0].warriors[1]->type],
                city[0].warriors[1]->id, city[0].warriors[1]->hp, city[0].warriors[1]->atk);
            city[0].last_reach_id = city[0].warriors[1]->id;
            city[0].reach_cnt++;
        }
    }
    if (city[0].reach_cnt == 2) {
        game_over = 1;
        printf("%03d:10 red headquarter was taken\n", cur_time / 60);
    }

    //// 各城市前进报告(红先蓝后)
    for (int i = 1; i <= N; i++) {
        if (city[i].warriors[0] != NULL)
            printf("%03d:10 red %s %d marched to city %d with %d elements and force %d\n",
                cur_time / 60, type_name[city[i].warriors[0]->type],
                city[i].warriors[0]->id, i, city[i].warriors[0]->hp, city[i].warriors[0]->atk);
        if (city[i].warriors[1] != NULL)
            printf("%03d:10 blue %s %d marched to city %d with %d elements and force %d\n",
                cur_time / 60, type_name[city[i].warriors[1]->type],
                city[i].warriors[1]->id, i, city[i].warriors[1]->hp, city[i].warriors[1]->atk);
    }

    //// 红武士到达蓝司令部的检测
    if (city[N + 1].warriors[0] != NULL) {
        if (city[N + 1].last_reach_id != city[N + 1].warriors[0]->id) {
            printf("%03d:10 red %s %d reached blue headquarter with %d elements and force %d\n",
                cur_time / 60, type_name[city[N + 1].warriors[0]->type],
                city[N + 1].warriors[0]->id, city[N + 1].warriors[0]->hp, city[N + 1].warriors[0]->atk);
            city[N + 1].last_reach_id = city[N + 1].warriors[0]->id;
            city[N + 1].reach_cnt++;
        }
    }
    if (city[N + 1].reach_cnt == 2) {
        game_over = 1;
        printf("%03d:10 blue headquarter was taken\n", cur_time / 60);
    }
}

//// 20分: 城市产出生命元
void add_elements() {
    for (int i = 1; i <= N; i++)
        city[i].elements += 10;
}

//// 30分: 独占城市的武士取走生命元
void get_elements() {
    for (int i = 1; i <= N; i++) {
        if (city[i].warriors[0] != NULL && city[i].warriors[1] == NULL) {
            printf("%03d:30 red %s %d earned %d elements for his headquarter\n",
                cur_time / 60, type_name[city[i].warriors[0]->type],
                city[i].warriors[0]->id, city[i].elements);
            city[0].elements += city[i].elements;
            city[i].elements = 0;
        }
        if (city[i].warriors[1] != NULL && city[i].warriors[0] == NULL) {
            printf("%03d:30 blue %s %d earned %d elements for his headquarter\n",
                cur_time / 60, type_name[city[i].warriors[1]->type],
                city[i].warriors[1]->id, city[i].elements);
            city[N + 1].elements += city[i].elements;
            city[i].elements = 0;
        }
    }
}

//// 35分: 放箭
void shoot_arrows() {
    for (int i = 0; i <= N + 1; i++) {
        //// 红武士(i)放箭射下一个城市(i+1)的蓝武士
        if (i != N + 1 && city[i].warriors[0] != NULL && city[i + 1].warriors[1] != NULL)
            city[i].warriors[0]->shoot_arrow(city[i + 1].warriors[1]);
        //// 蓝武士(i)放箭射前一个城市(i-1)的红武士
        if (i != 0 && city[i].warriors[1] != NULL && city[i - 1].warriors[0] != NULL)
            city[i].warriors[1]->shoot_arrow(city[i - 1].warriors[0]);
    }
}

//// 38分: 检查并使用bomb
void check_bomb() {
    for (int i = 1; i <= N; i++) {
        if (city[i].warriors[0] != NULL && city[i].warriors[1] != NULL) {
            if (city[i].warriors[0]->is_alive() && city[i].warriors[1]->is_alive()) {
                int fst = city[i].first_attacker();
                auto [p_dead, q_dead] = simulate_fight(city[i].warriors[fst], city[i].warriors[fst ^ 1]);
                if (p_dead) city[i].warriors[fst]->use_bomb(city[i].warriors[fst ^ 1]);
                if (q_dead) city[i].warriors[fst ^ 1]->use_bomb(city[i].warriors[fst]);
            }
        }
    }
    //// 清理同归于尽的双方
    for (int i = 1; i <= N; i++) {
        if (city[i].warriors[0] != NULL && city[i].warriors[1] != NULL) {
            if (!city[i].warriors[0]->is_alive() && !city[i].warriors[1]->is_alive())
                city[i].warriors[0] = city[i].warriors[1] = NULL;
        }
    }
}

//// 40分: 战斗
void fight() {
    //// 记录战斗前的HQ生命元(用于奖励)
    int orig_red = city[0].elements;
    int orig_blue = city[N + 1].elements;

    //// 逐个城市处理战斗
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].warriors[0] == NULL || city[i].warriors[1] == NULL) continue;
        int fst = city[i].first_attacker();

        //// 如果双方都活着(没被箭射死), 则发起攻击
        if (city[i].warriors[0]->is_alive() && city[i].warriors[1]->is_alive()) {
            city[i].warriors[fst]->attack_enemy(city[i].warriors[fst ^ 1]);
        }

        //// Dragon欢呼(士气变化+判断)
        if (city[i].warriors[fst]->is_alive())
            city[i].warriors[fst]->yell(!city[i].warriors[fst ^ 1]->is_alive(), 1);
        if (city[i].warriors[fst ^ 1]->is_alive())
            city[i].warriors[fst ^ 1]->yell(!city[i].warriors[fst]->is_alive(), 0);

        //// Wolf缴获武器
        if (city[i].warriors[fst]->is_alive() && !city[i].warriors[fst ^ 1]->is_alive())
            city[i].warriors[fst]->steal_weapon(city[i].warriors[fst ^ 1]);
        if (city[i].warriors[fst ^ 1]->is_alive() && !city[i].warriors[fst]->is_alive())
            city[i].warriors[fst ^ 1]->steal_weapon(city[i].warriors[fst]);

        //// 获胜方获取城市生命元
        if (city[i].warriors[0]->is_alive() && !city[i].warriors[1]->is_alive())
            city[i].warriors[0]->earn_elements();
        if (city[i].warriors[1]->is_alive() && !city[i].warriors[0]->is_alive())
            city[i].warriors[1]->earn_elements();

        //// 更新旗帜
        int red_alive = city[i].warriors[0]->is_alive();
        int blue_alive = city[i].warriors[1]->is_alive();
        if (red_alive && blue_alive)
            city[i].update_flag(-1);       // 平局
        else if (!red_alive && blue_alive)
            city[i].update_flag(1);        // 蓝方胜
        else if (red_alive && !blue_alive)
            city[i].update_flag(0);        // 红方胜
        else
            assert(0);  // 不会两方都死(炸弹情况已处理)
    }

    //// 奖励: 从远到近遍历，优先靠近敌方司令部的武士
    for (int i = N + 1; i >= 0; i--) {
        if (city[i].warriors[0] == NULL || city[i].warriors[1] == NULL) continue;
        if (city[i].warriors[0]->is_alive() && !city[i].warriors[1]->is_alive()) {
            if (orig_red >= 8) {
                orig_red -= 8;
                city[0].elements -= 8;
                city[i].warriors[0]->hp += 8;
            }
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].warriors[0] == NULL || city[i].warriors[1] == NULL) continue;
        if (city[i].warriors[1]->is_alive() && !city[i].warriors[0]->is_alive()) {
            if (orig_blue >= 8) {
                orig_blue -= 8;
                city[N + 1].elements -= 8;
                city[i].warriors[1]->hp += 8;
            }
        }
    }

    //// 清理战死的武士
    for (int i = 0; i <= N + 1; i++) {
        if (city[i].warriors[0] != NULL && !city[i].warriors[0]->is_alive())
            city[i].warriors[0] = NULL;
        if (city[i].warriors[1] != NULL && !city[i].warriors[1]->is_alive())
            city[i].warriors[1] = NULL;
    }
}

//// 50分: 司令部报告生命元
void hq_report() {
    printf("%03d:50 %d elements in red headquarter\n", cur_time / 60, city[0].elements);
    printf("%03d:50 %d elements in blue headquarter\n", cur_time / 60, city[N + 1].elements);
}

//// 55分: 武士报告武器
void warrior_report() {
    for (int i = 0; i <= N + 1; i++)
        if (city[i].warriors[0] != NULL)
            city[i].warriors[0]->report_weapon();
    for (int i = 0; i <= N + 1; i++)
        if (city[i].warriors[1] != NULL)
            city[i].warriors[1]->report_weapon();
}

//// 处理单组数据
void work() {
    cur_time = 0;
    game_over = 0;
    cin >> M >> N >> R >> K >> T;
    for (int i = 0; i < 5; i++) cin >> init_hp[i];
    for (int i = 0; i < 5; i++) cin >> init_atk[i];
    for (int i = 0; i < 25; i++) city[i] = City(i);
    city[0].elements = city[N + 1].elements = M;

    while (cur_time <= T) {
        //// 00分: 降生
        born();
        cur_time += 5;
        //// 05分: 逃跑
        if (cur_time > T) break;
        runaway();
        cur_time += 5;
        //// 10分: 前进
        if (cur_time > T) break;
        move_all();
        if (game_over) break;
        cur_time += 10;
        //// 20分: 城市产出生命元
        if (cur_time > T) break;
        add_elements();
        cur_time += 10;
        //// 30分: 独占取走生命元
        if (cur_time > T) break;
        get_elements();
        cur_time += 5;
        //// 35分: 放箭
        if (cur_time > T) break;
        shoot_arrows();
        cur_time += 3;
        //// 38分: 炸弹
        if (cur_time > T) break;
        check_bomb();
        cur_time += 2;
        //// 40分: 战斗
        if (cur_time > T) break;
        fight();
        cur_time += 10;
        //// 50分: 司令部报告
        if (cur_time > T) break;
        hq_report();
        cur_time += 5;
        //// 55分: 武士武器报告
        if (cur_time > T) break;
        warrior_report();
        cur_time += 5;
    }
}

int main() {
    int case_cnt;
    cin >> case_cnt;
    for (int i = 1; i <= case_cnt; i++) {
        printf("Case %d:\n", i);
        work();
    }
    return 0;
}