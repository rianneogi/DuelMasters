A computer game implementation of the Duel Masters card game with enforced rules

##Goals
-Online PvP

-Play against AI

-Campaign mode

##Dependencies
-The SFML Library

-Lua 5.1 for Windows

##How to create your own card
You can make your own cards through the Lua card API. Consider this card:

  <code>Cards["Aqua Hulcus"] = 
  {
  	name = "Aqua Hulcus",
  	set = "Base Set",
  	type = TYPE_CREATURE,
  	civilization = CIV_WATER,
  	race = "Liquid People",
  	cost = 3,
  
  	shieldtrigger = 0,
  	blocker = 0,
  
  	power = 2000,
  	breaker = 1,
  
  	HandleMessage = function(id)
  		Abils.drawOnSummon(id,1)
  	end
  }</code>
