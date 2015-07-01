TYPE_CREATURE = 0
TYPE_SPELL = 1

CIV_LIGHT = 0
CIV_NATURE = 1
CIV_WATER = 2
CIV_FIRE = 3
CIV_DARKNESS = 4

ZONE_HAND = 0
ZONE_DECK = 1
ZONE_BATTLE = 2
ZONE_MANA = 3
ZONE_SHIELD = 4
ZONE_GRAVEYARD = 5
ZONE_EVOLVED = 6

DEFENDER_CREATURE = 0
DEFENDER_PLAYER = 1

CANATTACK_TAPPED = 0
CANATTACK_UNTAPPED = 1
CANATTACK_NO = 2
CANATTACK_ALWAYS = 3

RETURN_BUTTON1 = -1
RETURN_BUTTON2 = -2
RETURN_NOVALID = -3
RETURN_NOTHING = -4

Abils = {}
Checks = {}
Actions = {}

getOpponent = function(p)
	if(p==1) then
		return 0
	else
		return 1
	end
end

Abils.Evolution = function(id,race)
    if(getMessageType()=="get creatureisevolution") then
        if(getMessageInt("creature")==id) then
            setMessageInt("isevolution",1)
        end
    end
    if(getMessageType()=="get creaturecanevolve") then
        if(getMessageInt("evolution")==id) then
            if(isCreatureOfRace(getMessageInt("evobait"),race)==1) then
                setMessageInt("canevolve",1)
            end
        end
    end
end

Abils.bonusPower = function(id, power)
    if(getMessageType()=="get creaturepower") then
		if(getMessageInt("creature")==id) then
			setMessageInt("power",getMessageInt("power")+power)
		end
	end
end

Abils.Blocker = function(id)
    if(getMessageType()=="get creatureisblocker") then
        if(getMessageInt("creature")==id) then
			setMessageInt("isblocker",1)
		end
    end
end

Abils.PowerAttacker = function(id, power)
	if(getMessageType()=="get creaturepower") then
		if(getMessageInt("creature")==id and getAttacker()==id) then
			setMessageInt("power",getMessageInt("power")+power)
		end
	end
end

Abils.SpeedAttacker = function(id)
    if(getMessageType()=="get creatureisspeedattacker") then
        if(getMessageInt("creature")==id) then
			setMessageInt("isspeedattacker",1)
		end
    end
end

Abils.Breaker = function(id,breakercount)
    if(getMessageType()=="get creaturebreaker") then
		if(getMessageInt("creature")==id) then
            if(getMessageInt("breaker") < breakercount) then
			    setMessageInt("breaker",breakercount)
            end
		end
	end
end

Abils.Slayer = function(id)
	if(getMessageType()=="post creaturebattle") then
		local att = getMessageInt("attacker")
		local def = getMessageInt("defender")
		if(att==id) then
			if(getCardZone(def)==ZONE_BATTLE) then
				destroyCreature(def)
			end
		end
		if(def==id) then
			if(getCardZone(att)==ZONE_BATTLE) then
				destroyCreature(att)
			end
		end
	end
end

Abils.Charger = function(id)
	if(getMessageType()=="mod cardmove") then
		if(getMessageInt("card")==id and getMessageInt("to")==ZONE_GRAVEYARD and getMessageInt("from")==ZONE_BATTLE) then
			setMessageInt("to",ZONE_MANA)
		end
	end
end

Abils.Survivor = function(id,func)
    if(getCardZone(id)==ZONE_BATTLE) then
        local owner = getCardOwner(id)
        local size = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(size-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(isCreatureOfRace(cid,"Survivor")==1) then
                func(cid)
            end
        end
    end
end

Abils.attacksEachTurn = function(id)
    --todo
end

Abils.cantAttack = function(id)
	if(getMessageType()=="get creaturecanattackcreature") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_NO)
		end
	end
    if(getMessageType()=="get creaturecanattackplayers") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_NO)
		end
	end
end

Abils.cantAttackCreatures = function(id)
	if(getMessageType()=="get creaturecanattackcreature") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_NO)
		end
	end
end

Abils.cantAttackPlayers = function(id)
	if(getMessageType()=="get creaturecanattackplayers") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_NO)
		end
	end
end

Abils.canAttackPlayersAlways = function(id)
    if(getMessageType()=="get creaturecanattackplayers") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_ALWAYS)
		end
	end
end

Abils.canAttackUntappedCreatures = function(id)
	if(getMessageType()=="get creaturecanattackcreature") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canattack",CANATTACK_UNTAPPED)
		end
	end
end

Abils.cantBeAttacked = function(id)
	if(getMessageType()=="get creaturecanattackcreature") then
		if(getMessageInt("defender")==id) then
			setMessageInt("canattack",CANATTACK_NO)
		end
	end
end

Abils.cantBeBlocked = function(id)
	if(getMessageType()=="get creaturecanblock") then
		if(getMessageInt("attacker")==id) then
			setMessageInt("canblock",0)
		end
	end
end

Abils.cantBeBlockedPower = function(id,power)
    if(getMessageType()=="get creaturecanblock") then
		if(getMessageInt("attacker")==id) then
            if(getCreaturePower(getMessageInt("blocker"))<=power) then
			    setMessageInt("canblock",0)
            end
		end
	end
end

Abils.destroyAfterBattle = function(id)
	if(getMessageType()=="post creaturebattle") then
		if(getMessageInt("attacker")==id or getMessageInt("defender")==id) then
			if(getCardZone(id)==ZONE_BATTLE) then
				destroyCreature(id)
			end
		end
	end
end

Abils.returnAfterDestroyed = function(id)
	if(getMessageType()=="mod creaturedestroy") then
		if(getMessageInt("creature")==id and getCardZone(id)==ZONE_BATTLE) then
			setMessageInt("zoneto",ZONE_HAND)
		end
	end
end

Abils.manaAfterDestroyed = function(id)
	if(getMessageType()=="mod creaturedestroy") then
		if(getMessageInt("creature")==id and getCardZone(id)==ZONE_BATTLE) then
			setMessageInt("zoneto",ZONE_MANA)
		end
	end
end

Abils.onSummon = function(id, func)
    if(getMessageType()=="post cardmove") then
		if(getMessageInt("card")==id and getMessageInt("to")==ZONE_BATTLE) then
            func(id)
        end
    end
end

Abils.drawOnSummon = function(id, count)
	func = function(id)
		drawCards(getTurn(),count)
	end
	Abils.onSummon(id,func)
end

Abils.destroyYourManaOnSummon = function(id, count)
    summon = function(id)
        for i=1,count do
            local ch = createChoice("Select mana to destroy",0,id,getCardOwner(id),Checks.InYourMana)
            if(ch>=0) then
                destroyMana(ch)
            end
        end
    end
    Abils.onSummon(id,summon)
end

Abils.destroyYourCreatureOnSummon = function(id, count)
    summon = function(id)
        for i=1,count do
            local ch = createChoice("Select creature to destroy",0,id,getCardOwner(id),Checks.InYourBattle)
            if(ch>=0) then
                destroyCreature(ch)
            end
        end
    end
    Abils.onSummon(id,summon)
end

Abils.onDestroy = function(id,func)
    if(getMessageType()=="post creaturedestroy") then
        if(getMessageInt("creature")==id) then
            func(id)
        end
    end
end

Abils.onAttack = function(id,func)
    if(getMessageType()=="post creatureattack") then
        if(getMessageInt("attacker")==id) then
            func(id)
        end
    end
end

Abils.drawCardsOnAttack = function(id,count)
    local func = function(id)
        drawCards(getCardOwner(id),count)
    end
    Abils.onAttack(id,func)
end

Abils.destroyOppManaOnAttack = function(id,count)
    local func = function(id)
        for i=1,count do
            local ch = createChoice("Select a card in opponent's mana",0,id,getCardOwner(id),Checks.InOppMana)
            if(ch>=0) then
                destroyMana(ch)
            end
        end
    end
    Abils.onAttack(id,func)
end

Abils.discardOppCardOnAttack = function(id,count)
    local func = function(id)
        for i=1,count do
            discardCardAtRandom(getOpponent(getCardOwner(id)))
        end
    end
    Abils.onAttack(id,func)
end

Abils.returnCreatureFromGraveyardOnAttack = function(id,count)
    local func = function(id)
        for i=1,count do
            local ch = createChoice("Select a creature in your graveyard",0,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
    end
    Abils.onAttack(id,func)
end

Abils.untapAtEOT = function(id,name)
    if(getMessageType()=="pre endturn") then
		if(getMessageInt("player")==getCardOwner(id) and getCardZone(id)==ZONE_BATTLE and isCardTapped(id)==1) then
			local ch = createChoiceNoCheck("Untap this creature?",2,id,getCardOwner(id),Checks.False)
			if(ch==RETURN_BUTTON1) then
                untapCard(id)
            end
		end
	end
end

Abils.destroyModAtEOT = function(cid,mid)
    if(getMessageType()=="pre endturn") then
		destroyModifier(cid,mid)
	end
end

Abils.destroyModAtSOT = function(cid,mid)
    if(getMessageType()=="pre startturn") then
		destroyModifier(cid,mid)
	end
end

Checks.InYourMana = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_MANA) then
		return 1
	else
		return 0
	end
end

Checks.CreatureInYourMana = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.SpellInYourMana = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardType(sid)==TYPE_SPELL) then
		return 1
	else
		return 0
	end
end

Checks.InOppMana = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_MANA) then
		return 1
	else
		return 0
	end
end

Checks.CreatureInOppMana = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.SpellInOppMana = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardType(sid)==TYPE_SPELL) then
		return 1
	else
		return 0
	end
end

Checks.InYourGraveyard = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_GRAVEYARD) then
		return 1
	else
		return 0
	end
end

Checks.CreatureInYourGraveyard = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_GRAVEYARD and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.SpellInYourGraveyard = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_GRAVEYARD and getCardType(sid)==TYPE_SPELL) then
		return 1
	else
		return 0
	end
end

Checks.InOppGraveyard = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_GRAVEYARD) then
		return 1
	else
		return 0
	end
end

Checks.InBattle = function(cid,sid)
	if(getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.InYourBattle = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.InOppBattle = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.UntappedInBattle = function(cid,sid)
	if(getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and isCardTapped(sid)==0) then
		return 1
	else
		return 0
	end
end

Checks.UntappedInYourBattle = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and isCardTapped(sid)==0) then
		return 1
	else
		return 0
	end
end

Checks.UntappedInOppBattle = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and isCardTapped(sid)==0) then
		return 1
	else
		return 0
	end
end

Checks.EvolutionInBattle = function(cid,sid)
	if(getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and getCreatureIsEvolution(sid)==1) then
		return 1
	else
		return 0
	end
end

Checks.EvolutionInYourBattle = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and getCreatureIsEvolution(sid)==1) then
		return 1
	else
		return 0
	end
end

Checks.EvolutionInOppBattle = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and getCreatureIsEvolution(sid)==1) then
		return 1
	else
		return 0
	end
end

Checks.BlockerInYourBattle = function(cid,sid)
    if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and getCreatureIsBlocker(sid)==1) then
		return 1
	else
		return 0
	end
end

Checks.BlockerInOppBattle = function(cid,sid)
    if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCardType(sid)==TYPE_CREATURE and getCreatureIsBlocker(sid)==1) then
		return 1
	else
		return 0
	end
end

Checks.InYourHand = function(cid,sid)
    if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_HAND) then
		return 1
	else
		return 0
	end
end

Checks.InYourDeck = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_DECK) then
		return 1
	else
		return 0
	end
end

Checks.SpellInYourDeck = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_DECK and getCardType(sid)==TYPE_SPELL) then
		return 1
	else
		return 0
	end
end

Checks.CreatureInYourDeck = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_DECK and getCardType(sid)==TYPE_CREATURE) then
		return 1
	else
		return 0
	end
end

Checks.InYourShields = function(cid,sid)
    if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_SHIELD) then
		return 1
	else
		return 0
	end
end

Checks.InOppShields = function(cid,sid)
    if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_SHIELD) then
		return 1
	else
		return 0
	end
end

Checks.True = function(cid,sid)
    return 1
end

Checks.False = function(cid,sid)
    return 0
end

Actions.SkipChoice = function(cid)
    setChoiceActive(0)
end

Actions.EndChoiceSpell = function(cid)
    --setChoiceActive(0)
    --moveCard(cid,ZONE_GRAVEYARD)
end

Actions.EndSpell = function(id)
    --moveCard(id,ZONE_GRAVEYARD)
end

Actions.execute = function(id,check,func)
    local x = getTotalCardCount()
    for i=0,(x-1) do
        if(check(id,i)==1) then
            func(id,i)
        end
    end
end

Actions.executeForCreaturesInBattle = function(id,player,func)
    local s = getZoneSize(player,ZONE_BATTLE)
    for i=0,(s-1) do
        local c = getCardAt(player,ZONE_BATTLE,i)
        if(getCardType(c)==TYPE_CREATURE) then
            func(id,c)
        end
    end
end

Actions.count = function(id,check)
    local x = getTotalCardCount()
    local count = 0
    for i=0,(x-1) do
        if(check(id,i)==1) then
            count=count+1
        end
    end
    return count
end

Actions.countTappedCreaturesInBattle = function(player)
    local size = getZoneSize(player,ZONE_BATTLE)
    local count = 0
    for i=0,(size-1) do
        local sid = getCardAt(player,ZONE_BATTLE,i)
        if(getCardType(sid)==TYPE_CREATURE and isCardTapped(sid)==1) then
            count = count+1
        end
    end
    return count
end

Actions.countCreaturesInBattle = function(player)
    local size = getZoneSize(player,ZONE_BATTLE)
    local count = 0
    for i=0,(size-1) do
        if(getCardType(getCardAt(player,ZONE_BATTLE,i))==TYPE_CREATURE) then
            count = count+1
        end
    end
    return count
end

Actions.moveTopCardsFromDeck = function(player,zone,count)
	local size = getZoneSize(player,ZONE_DECK)
    for i=1,count do
        if(i>size) then
            break
        end
        local c = getCardAt(player,ZONE_DECK,size-i)
	    moveCard(c,zone)
    end
end