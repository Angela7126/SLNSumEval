<html>
<head>
<meta name="TextLength" content="SENT_NUM:77, WORD_NUM:1563">
</head>
<body bgcolor="white">
<a href="#0" id="0">We have investigated conditions under which vendors may benefit from posting group or volume discounts for groups of buyers—assuming that buyers can coordinate their purchasing activities—relative to the posting of fixed prices.</a>
<a href="#1" id="1">We showed that, when facing i.i.d.</a>
<a href="#2" id="2">buyers that use the coordination mechanism of Lu and Boutilier [17], complex discount schedules cannot yield greater revenue than that generated using the optimal fixed price.</a>
<a href="#3" id="3">This holds whether vendors know the distribution of buyer types or simply the support of this distribution.</a>
<a href="#4" id="4">This is consistent with similar findings in other models of group buying (see Section 1.1).</a>
<a href="#5" id="5">This robust result highlights the fact that the design of effective pricing schemes for group buying should focus on settings where group discounts provide vendor value, including domains where buyer valuations are correlated by unobservable factors (such as perceived quality or advertising impact), marginal production costs are decreasing, vendors are risk-seeking, or where discounts have viral or long-term acquisition benefits.</a>
<a href="#6" id="6">We now outline several directions for future research, with an emphasis on equilibrium analysis and the connection to optimal auctions.</a>
<a href="#7" id="7">While this paper focused on the structure of a vendor's best-response, natural questions arise regarding to the existence and properties of (pure) Nash equilibria in our model.</a>
<a href="#8" id="8">Since our game has two steps, the appropriate solution concept is a subgame perfect equilibrium.</a>
<a href="#9" id="9">Formally, a (pure) subgame perfect equilibrium (SPE) of a complete information game {a mathematical formula}G=〈V,C〉 is a profile of discount schedules {a mathematical formula}P∈Pm such that no vendor j prefers {a mathematical formula}S=S(P,V) over {a mathematical formula}S′=S((p−j,pj′),V), for any {a mathematical formula}pj′∈P.</a>
<a href="#10" id="10">A fixed subgame perfect equilibrium (FSPE) in G is defined similarly, with the exception that only trivial (fixed price) schedules are allowed.</a>
<a href="#11" id="11">Note that an FSPE is neither a special case nor more general than an SPE since the restriction applies both the profile P and to the deviation {a mathematical formula}pj′.</a>
<a href="#12" id="12">However, by Proposition 1, the existence of an SPE in the full information model entails the existence of an FSPE with the same utilities for each vendor; and any FSPE is also an SPE in the full information model.</a>
<a href="#13" id="13">To illustrate, consider a game with two vendors (with zero costs), and two buyers.</a>
<a href="#14" id="14">Buyer a has preferences {a mathematical formula}va=(3,1) (i.e., a prefers vendor 1), whereas {a mathematical formula}vb=(1,3).</a>
<a href="#15" id="15">The fixed profile {a mathematical formula}P=(3,3) (i.e., {a mathematical formula}p1=3,p2=3) is an FSPE.</a>
<a href="#16" id="16">Each vendor has utility {a mathematical formula}Ui=3.</a>
<a href="#17" id="17">Any {a mathematical formula}pi′>3 will result in a utility of 0, whereas setting the price low enough to attract both buyers will result in a utility of at most 2.</a>
<a href="#18" id="18">When we consider the more complex models of partial information, we can construct similar definitions of SPE and FSPE using the already-defined concepts of best response.</a>
<a href="#19" id="19">For example, in the Bayesian model P is an SPE in the game {a mathematical formula}G=〈D,C〉 if {a mathematical formula}pj∈brjEU(pj,G) for all {a mathematical formula}j∈M.</a>
<a href="#20" id="20">Due to Theorem 3, Theorem 7, we know that under an i.i.d.</a>
<a href="#21" id="21">distribution any FSPE in the Bayesian/Distribution-free model is also an SPE.</a>
<a href="#22" id="22">However, this does not hold when the distribution is not i.i.d.</a>
<a href="#23" id="23">: in the examples described in proof of Proposition 4(a) and (b), the fixed profile {a mathematical formula}P⁎=(1,1) is an FSPE but not an SPE.</a>
<a href="#24" id="24">Also note that the existence of an SPE does not entail the existence of an FSPE, since the best response to a discount schedule might not be a fixed price (see Proposition 4(c)).</a>
<a href="#25" id="25">It is interesting to note that, in general, a (pure) SPE/FSPE may not exist at all—even in the complete information model and even when discounts are forbidden.</a>
<a href="#26" id="26">We now describe an example with two vendors and four buyers with known types that does not admit an FSPE (and by Proposition 1, no SPE).</a>
<a href="#27" id="27">Buyer types are: {a mathematical formula}a1=(9,0);a2=(0,9);b1=b2=(5,5).</a>
<a href="#28" id="28">Buyer {a mathematical formula}bi, {a mathematical formula}i∈{1,2}, has a weak preference to vendor i in the case of a tie.</a>
<a href="#29" id="29">Both vendors have zero cost.</a>
<a href="#30" id="30">It can be verified by detailed case analysis that given any fixed price profile {a mathematical formula}P=(p1,p2) there is at least one vendor who would raise or lower her price to improve her utility.</a>
<a href="#31" id="31">Let {a mathematical formula}x,y be the fixed prices offered by vendors 1 and 2, respectively.</a>
<a href="#32" id="32">We break our analysis into several cases, and show in each that at least one vendor can increase her utility by changing her price.</a>
<a href="#33" id="33">If {a mathematical formula}x>9 or {a mathematical formula}y>9 then the relevant vendor has no buyers and will lower his price to 9.</a>
<a href="#34" id="34">If {a mathematical formula}9>x>5 then {a mathematical formula}x′=9 is an improvement.</a>
<a href="#35" id="35">Likewise for {a mathematical formula}9>y>5.</a>
<a href="#36" id="36">If {a mathematical formula}x=y=9 then {a mathematical formula}y′=5 brings the utility of vendor 2 from {a mathematical formula}9⋅1 to {a mathematical formula}5⋅3=15.</a>
<a href="#37" id="37">If {a mathematical formula}x=9,y<5, then {a mathematical formula}y′=5 is an improvement.</a>
<a href="#38" id="38">Likewise for {a mathematical formula}y=9,x<5.</a>
<a href="#39" id="39">If {a mathematical formula}x=9,y=5, then {a mathematical formula}x′=5 increases the utility of vendor 1 to {a mathematical formula}5⋅2=10>9.</a>
<a href="#40" id="40">Similarly for {a mathematical formula}x=5,y=9.</a>
<a href="#41" id="41">If {a mathematical formula}x=y∈(4,5] then {a mathematical formula}x′=4 improves the utility of vendor 1 from {a mathematical formula}2x≤10 to {a mathematical formula}3(x′)=12.</a>
<a href="#42" id="42">Similarly, the higher vendor will deviate to 4 for any {a mathematical formula}x,y∈(4,5].</a>
<a href="#43" id="43">If {a mathematical formula}y≤x≤4 then {a mathematical formula}x′=9 improves the utility of vendor 1 from (at most) {a mathematical formula}2x≤8 to 9.</a>
<a href="#44" id="44">Similarly for vendor 2 if {a mathematical formula}x≤y≤4.</a>
<a href="#45" id="45">The last case is {a mathematical formula}y≤4,x∈(4,5].</a>
<a href="#46" id="46">Then {a mathematical formula}x′=9 improves the utility of vendor 1 from {a mathematical formula}x≤5 to 9.</a>
<a href="#47" id="47">Similarly for vendor 2 if {a mathematical formula}x≤4,y∈(4,5].</a>
<a href="#48" id="48">Intuitively, the market can be understood as follows.</a>
<a href="#49" id="49">Each vendor has some “core buyers” ({a mathematical formula}a1,a2 in our example), and “flexible buyers” that have no vendor preference and are influenced only by price ({a mathematical formula}b1,b2).</a>
<a href="#50" id="50">Suppose we start from a state where both prices are high.</a>
<a href="#51" id="51">The vendors compete for the flexible buyers by lowering prices, until at some point it is more worthwhile to one of the vendors (say 1) to opt out of the competition.</a>
<a href="#52" id="52">Then vendor 1 increases the price, keeping only its core buyers.</a>
<a href="#53" id="53">Now vendor 2 can also raise its price since there is no competition, and we are back in the start state.</a>
<a href="#54" id="54">Developing conditions under which pure SPE and FPSE exist is of great interest, especially in cases where all vendors use group discounts.</a>
<a href="#55" id="55">In his seminal study on optimal auctions, Myerson [21] characterized truthful auction mechanisms, showing that when a seller with a single good faces i.i.d.</a>
<a href="#56" id="56">buyers, the optimal mechanism is effectively a second-price auction with a fixed reserve price.</a>
<a href="#57" id="57">In a related analysis of a model closer to our model, Goldberg et al. [10] show that the worst-case revenue of using a fixed price to sell digital goods (i.e., unlimited supply) is at least as great as that any other truthful “auction” mechanism.</a>
<a href="#58" id="58">They also provided bounds on the revenue attainable by such a mechanism when compared to a variety of benchmarks, which later became standard in the literature.</a>
<a href="#59" id="59">Consider the following auction rule that sets a price for bidder i, when submitted bids are {a mathematical formula}(b1,…,bn): “if there are at least {a mathematical formula}k−1 other bidders s.t.</a>
<a href="#60" id="60">{a mathematical formula}bj≥p(k), then allocate an item to i for a price of {a mathematical formula}pi=q(k)”.</a>
<a href="#61" id="61">Clearly the outcome of such an auction is equivalent to the outcome of posting the discount schedule q. Moreover, the allocation rule is monotone in the bid, and the price {a mathematical formula}pi is independent of {a mathematical formula}bi.</a>
<a href="#62" id="62">Thus according to Myerson, this auction is truthful.</a>
<a href="#63" id="63">While the Goldberg et al. paper does not deal with a Bayesian setting, it is known that the result still holds when bidder valuations are sampled i.i.d.</a>
<a href="#64" id="64">from some distribution.</a>
<a href="#65" id="65">It would be interesting to study the relationship between optimal truthful mechanisms and group discount mechanisms in more depth in various settings.</a>
<a href="#66" id="66">{sup:5}</a>
<a href="#67" id="67">Within our current model, further research is needed to understand the full impact of group discounts when buyer valuations are correlated by signals—such as product quality, vendor reputation, or advertising.</a>
<a href="#68" id="68">Even for a monopolist, the question of computing optimal discount schedules (given a correlated distribution over buyer types) is non-trivial.</a>
<a href="#69" id="69">When facing competing vendors the problem becomes even more complex.</a>
<a href="#70" id="70">It is therefore important to identify natural classes of distributions where optimal or near-optimal schedules can be computed efficiently.</a>
<a href="#71" id="71">Another interesting question is what to expect when buyers use stronger coordination mechanisms, such as those that allow transferable utility[26], [17].</a>
<a href="#72" id="72">We conjecture that our main result about the optimality of a fixed price when buyers are i.i.d.</a>
<a href="#73" id="73">still holds under different variations such as transferable utility.</a>
<a href="#74" id="74">Network externalities is the common name for the phenomenon where buyers assign utility to sharing a vendor or a service (such as a cellular provider or online social network) [13], [3], [9].</a>
<a href="#75" id="75">One way to think of group discounts is in terms of adding indirect network externalities to the interaction among buyers—the interactions are indirect in the sense that they mediated by the vendors (or by arbitrators of buying groups) and depend on vendor strategies, with the buyers themselves potentially even unaware of the choices of other buyers.</a>
<a href="#76" id="76">Incorporating network structure into our model of group discounts may also be very relevant, as such structure may determine which groups of buyers are able or are likely to coordinate—especially in the context of transferable utility.</a>
</body>
</html>