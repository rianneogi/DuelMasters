package.path = package.path .. ';./?.lua;'
require("Shadowclash")

Cards["Ambush Scorpion"] = {
	name = "Ambush Scorpion",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Angel Command",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.PowerAttacker(id,3000)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.InYourMana(cid,sid)==1 and getCardName(sid)=="Ambush Scorpion") then
                    return 1
                else
                    return 0
                end
            end
            local ch = createChoice("Choose an Ambush Scorpion in your mana zone",1,id,getCardOwner(id),valid)
            if(ch>=0) then
                moveCard(ch,ZONE_BATTLE)
            end
        end
        Abils.onDestroy(id,func)
	end
}

Cards["Aqua Surfer"] = {
	name = "Aqua Surfer",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Angel Command",
	cost = 6,

	shieldtrigger = 1,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Select creature in battle zone",1,att,getCardOwner(id),Checks.InBattle)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
		Abils.onSummon(id,func)
	end
}

Cards["Avalanche Giant"] = {
	name = "Avalanche Giant",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.cantAttackCreatures(id)
        if(getMessageType()=="post creatureblock") then
            if(getMessageInt("attacker")==id) then
                local ch = createChoice("Choose an opponent's shield",0,id,getCardOwner(id),Checks.InOppShields)
                if(ch>=0) then
                    creatureBreakShield(id,ch)
                end
            end
        end
	end
}

Cards["Balloonshroom Q"] = {
	name = "Balloonshroom Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Balloon Mushroom/Survivor",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.manaAfterDestroyed(cid)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Ballus, Dogfight Enforcer Q"] = {
	name = "Ballus, Dogfight Enforcer Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker/Survivor",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            if(getMessageType()=="pre endturn") then
		        if(getMessageInt("player")==getCardOwner(id) and getCardZone(id)==ZONE_BATTLE and isCardTapped(id)==1) then
                    untapCard(id)
		        end
            end
        end
        Abils.Survivor(id,func)
	end
}

Cards["Billion-Degree Dragon"] = {
	name = "Billion-Degree Dragon",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 10,

	shieldtrigger = 0,
	blocker = 0,

	power = 15000,
	breaker = 3,

	HandleMessage = function(id)
	end
}

Cards["Bladerush Skyterror Q"] = {
	name = "Bladerush Skyterror Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern/Survivor",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.Breaker(cid,2)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Blazosaur Q"] = {
	name = "Blazosaur Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast/Survivor",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.PowerAttacker(cid,1000)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Bloodwing Mantis"] = {
	name = "Bloodwing Mantis",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a creature in your mana zone",0,id,getCardOwner(id),Checks.CreatureInYourMana)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                local ch2 = createChoice("Choose a creature in your mana zone",0,id,getCardOwner(id),Checks.CreatureInYourMana)
                if(ch2>=0) then
                    moveCard(ch2,ZONE_HAND)
                end
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Bolgash Dragon"] = {
	name = "Bolgash Dragon",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 3,

	HandleMessage = function(id)
        Abils.PowerAttacker(id,8000)
	end
}

Cards["Bombat, General of Speed"] = {
	name = "Bombat, General of Speed",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
    race = "Dragonoid",
	cost = 5,

	shieldtrigger = 0,
    blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.SpeedAttacker(id)
	end
}

Cards["Brutal Charge"] = {
	name = "Brutal Charge",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 5,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Calgo, Vizier of Rainclouds"] = {
	name = "Calgo, Vizier of Rainclouds",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
    race = "Initiate",
	cost = 3,

	shieldtrigger = 0,
    blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanblock") then
		    if(getMessageInt("attacker")==id) then
                if(getCreaturePower(getMessageInt("blocker"))>=4000) then
			        setMessageInt("canblock",0)
                end
		    end
	    end
	end
}

Cards["Cannoneer Bargon"] = {
	name = "Cannoneer Bargon",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
    race = "Armoloid",
	cost = 4,

	shieldtrigger = 1,
    blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantAttackPlayers(id)
	end
}

Cards["Cataclysmic Eruption"] = {
	name = "Dew Mushroom",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 8,

	shieldtrigger = 0,

	OnCast = function(id)
        local owner = getCardOwner(id)
        local size = getZoneSize(owner,ZONE_BATTLE)
        local cwn= 0
        for i=0,(size-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardType(cid)==TYPE_CREATURE) then
                local civ = getCardCiv(cid)
                if(civ==CIV_NATURE) then
                    cwn= cn+1
                end
            end
        end
        for i=1,cn do
            local ch = createChoice("Choose a card in your opponent's mana zone",1,id,getCardOwner(id),Checks.InOppMana)
            if(ch>=0) then
                destroyMana(ch)
            end
            if(ch==RETURN_NOVALID or ch==RETURN_BUTTON1) then
                break
            end
        end
        Functions.EndSpell(id)
	end
}

Cards["Crow Winger"] = {
	name = "Crow Winger",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturepower") then
            if(getMessageInt("creature")==id) then
                local owner = getOpponent(getCardOwner(id))
                local size = getZoneSize(owner,ZONE_BATTLE)
                local count = 0
                local cid
                local civ
                for i=0,(size-1) do
                    cid = getCardAt(owner,ZONE_BATTLE,i)
                    civ = getCardCiv(cid)
                    if(civ==CIV_WATER or civ==CIV_DARKNESS) then
                        count = count+1
                    end
                end
                Abils.bonusPower(id,count*1000)
            end
        end
	end
}

Cards["Cyclone Panic"] = {
	name = "Cyclone Panic",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 3,

	shieldtrigger = 1,

	OnCast = function(id)
        for i=0,1 do
            local size = getZoneSize(i,ZONE_HAND)
            for j=0,(size-1) do
                moveCard(getCardAt(i,ZONE_HAND,j),ZONE_DECK)
            end
            shuffleDeck(i)
            drawCards(i,size)
        end
        Functions.EndSpell(id)
	end
}

Cards["Death Cruzer, the Annihilator"] = {
	name = "Death Cruzer, the Annihilator",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 13000,
	breaker = 3,

	HandleMessage = function(id)
        local func = function(id)
            local func = function(cid,sid)
                if(sid~=cid) then
                    destroyCreature(sid)
                end
            end
            Functions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        end
        Abils.onSummon(id)
	end
}

Cards["Divine Riptide"] = {
	name = "Divine Riptide",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 9,

	shieldtrigger = 0,

	OnCast = function(id)
        local valid = function(cid,sid)
            if(Checks.InYourMana(cid,sid)==1 or Checks.InOppMana(cid,sid)==1) then
                return 1
            else
                return 0
            end
        end
        local func = function(cid,sid)
            moveCard(sid,ZONE_HAND)
        end
        Functions.execute(id,valid,func)
        Functions.EndSpell(id)
	end
}

Cards["Enchanted Soil"] = {
	name = "Enchanted Soil",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        local ch = createChoice("Choose 2 creatures in your graveyard",1,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
        if(ch>=0) then
            moveCard(ch,ZONE_MANA)
            local ch2 = createChoice("Choose 2 creatures in your graveyard",1,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
            if(ch2>=0) then
                moveCard(ch2,ZONE_MANA)
            end
        end
        Functions.EndSpell(id)
	end
}

Cards["Gallia Zohl, Iron Guardian Q"] = {
	name = "Gallia Zohl, Iron Guardian Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian/Survivor",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.Blocker(cid)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Gigakail"] = {
	name = "Gigakail",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="post creaturebattle") then
		    local att = getMessageInt("attacker")
		    local def = getMessageInt("defender")
		    if(att==id) then
			    if(getCardZone(def)==ZONE_BATTLE and (getCardCiv(def)==CIV_LIGHT or getCardCiv(def)==CIV_NATURE)) then
				    destroyCreature(def)
			    end
		    end
		    if(def==id) then
			    if(getCardZone(att)==ZONE_BATTLE and (getCardCiv(att)==CIV_LIGHT or getCardCiv(att)==CIV_NATURE)) then
				    destroyCreature(att)
			    end
		    end
	    end
	end
}

Cards["Gigaling Q"] = {
	name = "Gigaling Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera/Survivor",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.Slayer(cid)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Gigazoul"] = {
	name = "Gigazoul",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanattackcreature") then
		    if(getMessageInt("attacker")==id) then
                if(getZoneSize(getOpponent(getCardOwner(id)),ZONE_SHIELD)==0) then
			        setMessageInt("canattack",CANATTACK_NO)
                end
		    end
	    end
        if(getMessageType()=="get creaturecanattackplayers") then
		    if(getMessageInt("attacker")==id) then
			    if(getZoneSize(getOpponent(getCardOwner(id)),ZONE_SHIELD)==0) then
			        setMessageInt("canattack",CANATTACK_NO)
                end
		    end
	    end
	end
}

Cards["Glory Snow"] = {
	name = "Glory Snow",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 4,

	shieldtrigger = 1,

	OnCast = function(id)
        local owner = getCardOwner(id)
        local c1 = getZoneSize(owner)
        local c2 = getZoneSize(getOpponent(owner))
        if(c2>c1) then
            Functions.moveTopCardsFromDeck(owner,ZONE_MANA,2)
        end
        Functions.EndSpell(id)
	end
}

Cards["Horned Mutant"] = {
	name = "Horned Mutant",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 5,

	shieldtrigger = 0,
    blocker = 0,

	power = 3000,
	breaker = 1,

	OnCast = function(id)
        if(getMessageType()=="get cardcost") then
            if(getCardZone(id)==ZONE_BATTLE) then
                local card = getMessageInt("card")
                if(getCardCiv(card)==CIV_LIGHT) then
                    local cost = getMessageInt("cost")
                    setMessageInt("cost",cost+1)
                end
            end
        end
	end
}

Cards["Jewel Spider"] = {
	name = "Jewel Spider",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Bain Jacker",
	cost = 2,

	shieldtrigger = 1,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose one of your shields",0,id,getCardOwner(id),Checks.InYourShields)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
        Abils.onDestroy(id,func)
	end
}

Cards["King Mazelan"] = {
	name = "King Mazelan",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Select creature in battle zone",1,att,getCardOwner(id),Checks.InBattle)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
		Abils.onSummon(id,func)
	end
}

Cards["King Tsunami"] = {
	name = "King Tsunami",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 12,

	shieldtrigger = 0,
	blocker = 0,

	power = 12000,
	breaker = 3,

	HandleMessage = function(id)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.InBattle(cid,sid)==0 and cid~=sid) then
                    return 1
                else
                    return 0
                end
            end
            local exec = function(cid,sid)
                moveCard(sid,ZONE_HAND)
            end
            Functions.execute(id,valid,exec)
        end
		Abils.onSummon(id,func)
	end
}

Cards["Kip Chippotto"] = {
	name = "Kip Chippotto",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Fire Bird",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Kulus, Soulshine Enforcer"] = {
	name = "Kulus, Soulshine Enforcer",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker",
	cost = 4,

	shieldtrigger = 1,
	blocker = 0,

	power = 3500,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local owner = getCardOwner(id)
            local c1 = getZoneSize(owner)
            local c2 = getZoneSize(getOpponent(owner))
            if(c2>c1) then
                Functions.moveTopCardsFromDeck(owner,ZONE_MANA,1)
            end
        end
        Abils.onSummon(func,id)
	end
}

Cards["La Byle, Seeker of the Winds"] = {
	name = "La Byle, Seeker of the Winds",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Mecha Thunder",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["La Guile, Seeker of Skyfire"] = {
	name = "La Guile, Seeker of Skyfire",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Mecha Thunder",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Le Quist, the Oracle"] = {
	name = "Le Quist, the Oracle",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
    race = "Light Bringer",
	cost = 2,

	shieldtrigger = 0,
    blocker = 0,

	power = 1500,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.UntappedInBattle(cid,sid)==1 and (getCardCiv(sid)==CIV_FIRE or getCardCiv(sid)==CIV_DARKNESS)) then
                    return 1
                else
                    return 0
                end
            end
            local ch = createChoice("Choose a creature",1,id,getCardOwner(id),valid)
            if(ch>=0) then
                tapCard(ch)
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Lurking Eel"] = {
	name = "Lurking Eel",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanblock") then
		    if(getMessageInt("blocker")==id) then
                if(getCardCiv(getMessageInt("attacker"))~=CIV_NATURE and getCardCiv(getMessageInt("attacker"))~=CIV_FIRE) then
			        setMessageInt("canblock",0)
                end
		    end
	    end
	end
}

Cards["Miracle Quest"] = {
	name = "Miracle Quest",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 3,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Moon Horn"] = {
	name = "Moon Horn",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturepower") then
            if(getMessageInt("creature")==id) then
                local owner = getOpponent(getCardOwner(id))
                local size = getZoneSize(owner,ZONE_BATTLE)
                local count = 0
                local cid
                local civ
                for i=0,(size-1) do
                    cid = getCardAt(owner,ZONE_BATTLE,i)
                    civ = getCardCiv(cid)
                    if(civ==CIV_WATER or civ==CIV_DARKNESS) then
                        count = count+1
                    end
                end
                Abils.bonusPower(id,count*1000)
            end
        end
	end
}

Cards["Nocturnal Giant"] = {
	name = "Nocturnal Giant",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 3,

	HandleMessage = function(id)
        Abils.cantAttackCreatures(id)
        Abils.PowerAttacker(id,7000)
	end
}

Cards["Obsidian Scarab"] = {
	name = "Obsidian Scarab",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
    race = "Giant Insect",
	cost = 6,

	shieldtrigger = 0,
    blocker = 0,

	power = 5000,
	breaker = 2,

	OnCast = function(id)
        Abils.PowerAttacker(id,3000)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.InYourMana(cid,sid)==1 and getCardName(sid)=="Obsidian Scarab") then
                    return 1
                else
                    return 0
                end
            end
            local ch = createChoice("Choose an Obsidian Scarab in your mana zone",1,id,getCardOwner(id),valid)
            if(ch>=0) then
                moveCard(ch,ZONE_BATTLE)
            end
        end
        Abils.onDestroy(id,func)
	end
}

Cards["Pokolul"] = {
	name = "Pokolul",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Lord",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Rikabu, the Dismantler"] = {
	name = "Rikabu, the Dismantler",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Machine Eater",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.SpeedAttacker(id)
	end
}

Cards["Ruthless Skyterror"] = {
	name = "Ruthless Skyterror",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantAttackPlayers(id)
        if(getMessageType()=="get creaturecanattackcreature") then
		    if(getMessageInt("attacker")==id and getCardCiv(getMessageInt("defender"))==CIV_WATER) then
			    setMessageInt("canattack",CANATTACK_UNTAPPED)
		    end
	    end
	end
}

Cards["Scheming Hands"] = {
	name = "Scheming Hands",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 5,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Scissor Scarab"] = {
	name = "Scissor Scarab",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.CreatureInYourDeck(cid,sid)==1 and getCreatureRace(sid)=="Giant Insect") then
                    return 1
                else
                    return 0
                end
            end
            local owner = getCardOwner(id)
            openDeck(owner)
            local ch = createChoice("Choose a Giant Insect in your deck",1,id,owner,valid)
            closeDeck(owner)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                shuffleDeck(owner)
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Sea Slug"] = {
	name = "Sea Slug",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 8,

	shieldtrigger = 0,
	blocker = 1,

	power = 6000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantBeBlocked(id)
	end
}

Cards["Sinister General Damudo"] = {
	name = "Sinister General Damudo",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Dark Lord",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.InBattle(cid,sid)==1 and getCreaturePower(sid)<=3000) then
                    return 1
                else
                    return 0
                end
            end
            local exec = function(cid,sid)
                destroyCreature(sid)
            end
            Functions.execute(id,valid,exec)
        end
        Abils.onDestroy(id,func)
	end
}

Cards["Skullsweeper Q"] = {
	name = "Skullsweeper Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Brain Jacker/Survivor",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.discardOppCardOnAttack(cid,1)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Slime Veil"] = {
	name = "Slime Veil",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 1,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Smash Horn Q"] = {
	name = "Smash Horn Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast/Survivor",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.bonusPower(cid,1000)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Snork La, Shrine Guardian"] = {
	name = "Snork La, Shrine Guardian",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Solidskin Fish"] = {
	name = "Solidskin Fish",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Fish",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
            if(ch>=0) then
                moveCard(ZONE_HAND)
            end
        end
	end
}

Cards["Spikestrike Ichthys Q"] = {
	name = "Spikestrike Ichthys Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
    race = "Fish/Survivor",
	cost = 6,

	shieldtrigger = 0,
    blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.cantBeBlocked(cid)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Split-Head Hydroturtle Q"] = {
	name = "Split-Head Hydroturtle Q",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish/Survivor",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(cid)
            Abils.drawCardsOnAttack(cid,1)
        end
        Abils.Survivor(id,func)
	end
}

Cards["Steel-Turret Cluster"] = {
	name = "Steel-Turret Cluster",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
    race = "Cyber Cluster",
	cost = 5,

	shieldtrigger = 0,
    blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanattackcreature") then
		    if(getMessageInt("defender")==id) then
                local civ = getCardCiv(getMessageInt("attacker"))
                if(civ==CIV_NATURE or civ==CIV_FIRE) then
			        setMessageInt("canattack",CANATTACK_NO)
                end
		    end
	    end
	end
}

Cards["Syforce, Aurora Elemental"] = {
	name = "Syforce, Aurora Elemental",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
    race = "Angel Command",
	cost = 7,

	shieldtrigger = 0,
    blocker = 1,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a spell in your mana zone",1,id,getCardOwner(id),Checks.SpellInYourMana)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Syrius, Firmament Elemental"] = {
	name = "Syrius, Firmament Elemental",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 11,

	shieldtrigger = 0,
	blocker = 1,

	power = 12000,
	breaker = 3,

	HandleMessage = function(id)
	end
}

Cards["Thunder Net"] = {
	name = "Thunder Net",
	set = "Survivors of the Megapocalypse",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 2,

	shieldtrigger = 0,

	OnCast = function(id)
        local owner = getCardOwner(id)
        local size = getZoneSize(owner,ZONE_BATTLE)
        local cw = 0
        for i=0,(size-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardType(cid)==TYPE_CREATURE) then
                local civ = getCardCiv(cid)
                if(civ==CIV_WATER) then  
                    cw = cw+1
                end
            end
        end
        for i=1,cw do
            local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
            if(ch>=0) then
                tapCard(ch)
            end
            if(ch==RETURN_NOVALID or ch==RETURN_BUTTON1) then
                break
            end
        end
        Functions.EndSpell(id)
	end
}

Cards["Twin-Cannon Skyterror"] = {
	name = "Twin-Cannon Skyterror",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.SpeedAttacker(id)
	end
}

Cards["Vashuna, Sword Dancer"] = {
	name = "Vashuna, Sword Dancer",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanattackcreature") then
		    if(getMessageInt("attacker")==id) then
                if(getZoneSize(getOpponent(getCardOwner(id)),ZONE_SHIELD)==0) then
			        setMessageInt("canattack",CANATTACK_NO)
                end
		    end
	    end
        if(getMessageType()=="get creaturecanattackplayers") then
		    if(getMessageInt("attacker")==id) then
			    if(getZoneSize(getOpponent(getCardOwner(id)),ZONE_SHIELD)==0) then
			        setMessageInt("canattack",CANATTACK_NO)
                end
		    end
	    end
	end
}

Cards["Wisp Howler, Shadow of Tears"] = {
	name = "Wisp Howler, Shadow of Tears",
	set = "Survivors of the Megapocalypse",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
    race = "Ghost",
	cost = 3,

	shieldtrigger = 0,
    blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="post creaturebattle") then
		    local att = getMessageInt("attacker")
		    local def = getMessageInt("defender")
		    if(att==id) then
			    if(getCardZone(def)==ZONE_BATTLE and (getCardCiv(def)==CIV_LIGHT or getCardCiv(def)==CIV_NATURE)) then
				    destroyCreature(def)
			    end
		    end
		    if(def==id) then
			    if(getCardZone(att)==ZONE_BATTLE and (getCardCiv(att)==CIV_LIGHT or getCardCiv(att)==CIV_NATURE)) then
				    destroyCreature(att)
			    end
		    end
	    end
	end
}