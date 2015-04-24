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

DEFENDER_CREATURE = 0
DEFENDER_PLAYER = 1

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

Abils.PowerAttacker = function(id, power)
	if(getMessageType()=="get creaturepower") then
		if(getMessageInt("creature")==id and getAttacker()==id) then
			setMessageInt("power",getMessageInt("power")+power)
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
				destroyCard(def)
			end
		end
		if(def==id) then
			if(getCardZone(att)==ZONE_BATTLE) then
				destroyCard(att)
			end
		end
	end
end

Abils.cantAttack = function(id)
	if(getMessageType()=="get creaturecanattack") then
		if(getMessageInt("creature")==id) then
			setMessageInt("canattack",0)
		end
	end
end

Abils.cantAttackCreatures = function(id)
	if(getMessageType()=="get creaturecanattackcreatures") then
		if(getMessageInt("creature")==id) then
			setMessageInt("canattackcreatures",0)
		end
	end
end

Abils.cantAttackPlayers = function(id)
	if(getMessageType()=="get creaturecanattackplayers") then
		if(getMessageInt("creature")==id) then
			setMessageInt("canattackplayers",0)
		end
	end
end

Abils.canAttackUntappedCreatures = function(id)
	if(getMessageType()=="get creaturecanattackuntappedcreatures") then
		if(getMessageInt("creature")==id) then
			setMessageInt("canattackuntappedcreatures",1)
		end
	end
end

Abils.cantBeBlocked = function(id)
	if(getMessageType()=="get creaturecanbeblocked") then
		if(getMessageInt("creature")==id) then
			setMessageInt("canbeblocked",0)
		end
	end
end

Abils.destroyAfterBattle = function(id)
	if(getMessageType()=="post creaturebattle") then
		if(getMessageInt("attacker")==id or getMessageInt("defender")==id) then
			if(getCardZone(id)==ZONE_BATTLE) then
				destroyCard(id)
			end
		end
	end
end

Abils.returnAfterDestroyed = function(id)
	if(getMessageType()=="mod carddestroy") then
		if(getMessageInt("card")==id) then
			setMessageInt("zoneto",ZONE_HAND)
		end
	end
end

Abils.manaAfterDestroyed = function(id)
	if(getMessageType()=="mod carddestroy") then
		if(getMessageInt("card")==id) then
			setMessageInt("zoneto",ZONE_MANA)
		end
	end
end

Abils.drawOnSummon = function(id, count)
	if(getMessageType()=="post cardmove") then
		if(getMessageInt("card")==id) then
			if(getMessageInt("to")==ZONE_BATTLE) then
				drawCards(getTurn(),count)
			end
		end
	end
end

Abils.destroyYourManaOnSummon = function(id, count)
	if(getMessageType()=="post cardmove") then
		if(getMessageInt("card")==id) then
			createChoice("Select mana to destroy",0,id)
			choicePushSelect(2,"Actions","destroy")
			choicePushValid(2,"Checks","InYourMana")
		end
	end
end

Abils.destroyYourCreatureOnSummon = function(id, count)
	if(getMessageType()=="post cardmove") then
		if(getMessageInt("card")==id) then
			createChoice("Select creature to destroy",0,id)
			choicePushSelect(2,"Actions","destroy")
			choicePushValid(2,"Checks","InYourBattle")
		end
	end
end

Abils.destroyModAtEOT = function(cid,mid)
    if(getMessageType()=="pre endturn") then
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

Checks.InOppMana = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_MANA) then
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

Checks.InOppGraveyard = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_GRAVEYARD) then
		return 1
	else
		return 0
	end
end

Checks.InBattle = function(cid,sid)
	if(getCardZone(sid)==ZONE_BATTLE) then
		return 1
	else
		return 0
	end
end

Checks.InYourBattle = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE) then
		return 1
	else
		return 0
	end
end

Checks.InOppBattle = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE) then
		return 1
	else
		return 0
	end
end

Checks.UntappedInYourBattle = function(cid,sid)
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and isCardTapped(sid)==0) then
		return 1
	else
		return 0
	end
end

Checks.UntappedInOppBattle = function(cid,sid)
	if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and isCardTapped(sid)==0) then
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
	if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_DECK and getCardType(sid)==TYPE_Creature) then
		return 1
	else
		return 0
	end
end

Actions.SkipChoice = function(cid)
    setChoiceActive(0)
end

Actions.EndChoiceSpell = function(cid)
    setChoiceActive(0)
    moveCard(cid,ZONE_GRAVEYARD)
end

Actions.EndSpell = function(id)
    moveCard(id,ZONE_GRAVEYARD)
end
