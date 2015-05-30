package.path = package.path .. ';./?.lua;'
require("BaseSet")

Cards["Amber Piercer"] = {
	name = "Amber Piercer",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Brain Jacker",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.returnCreatureFromGraveyardOnAttack(id,1)
	end
}

Cards["Aqua Bouncer"] = {
	name = "Aqua Bouncer",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 1000,
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

Cards["Aqua Shooter"] = {
	name = "Aqua Shooter",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 4,

	shieldtrigger = 0,
	blocker = 1,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Armored Blaster Valdios"] = {
	name = "Armored Blaster Valdios",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Armored Cannon Balbaro"] = {
	name = "Armored Cannon Balbaro",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Barkwhip, the Smasher"] = {
	name = "Barkwhip, the Smasher",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Bolzard Dragon"] = {
	name = "Bolzard Dragon",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.destroyOppManaOnAttack(id,1)
	end
}

Cards["Bombersaur"] = {
	name = "Bombersaur",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="post carddestroy") then
            if(getMessageInt("card")==id) then
                local ch = createChoice("Destroy a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
                ch = createChoice("Destroy a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
                ch = createChoice("Destroy a card in your mana zone",0,id,getOpponent(getCardOwner(id)),Checks.InOppMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
                ch = createChoice("Destroy a card in your mana zone",0,id,getOpponent(getCardOwner(id)),Checks.InOppMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
            end
        end
	end
}

Cards["Burst Shot"] = {
	name = "Burst Shot",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 6,

	shieldtrigger = 1,

	OnCast = function(id)
        local owner = getCardOwner(id)
        local size = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(size-1) do
            local card = getCardAt(owner,ZONE_BATTLE,i)
            if(getCreaturePower(card)<=2000) then
                destroyCard(card)
            end
        end
        owner = getOpponent(owner)
        size = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(size-1) do
            local card = getCardAt(owner,ZONE_BATTLE,i)
            if(getCreaturePower(card)<=2000) then
                destroyCard(card)
            end
        end
        Actions.EndSpell(id)
	end
}

Cards["Cavalry General Curatops"] = {
	name = "Cavalry General Curatops",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.canAttackUntappedCreatures(id)
	end
}

Cards["Chaos Worm"] = {
    name = "Chaos Worm",
    set = "Evo-Crushinators of Doom"

}

Cards["Corile"] = {
    name = "Corile",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Lord",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Critical Blade"] = {
    name = "Critical Blade",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 2,

	shieldtrigger = 1,

	OnCast = function(id)
        local ch = createChoice("Choose opponent's blocker",0,id,getCardOwner(id),Checks.BlockerInOppBattle)
        if(ch>=0) then
            destroyCard(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Crystal Lancer"] = {
    name = "Crystal Lancer",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Crystal Paladin"] = {
    name = "Crystal Paladin",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Dark Titan Maginn"] = {
    name = "Dark Titan Maginn",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Diamond Cutter"] = {
    name = "Diamond Cutter",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

    OnCast = function(id)
        --todo
    end
}

Cards["Dogarn, the Marauder"] = {
    name = "Dogarn, the Marauder",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armorloid",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

    HandleMessage = function(id)
        local c = Actions.countTappedCreaturesInBattle(getCardOwner(id))-1
        Abils.PowerAttacker(id,c*2000)
    end
}

Cards["Elf-X"] = {
    name = "Elf-X",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

    HandleMessage = function(id)
        if(getMessageType()=="get cardcost") then
            if(getCardZone(id)==ZONE_BATTLE) then
                if(getCardType(getMessageInt("card"))==TYPE_CREATURE) then
                    local cost = getMessageInt("cost")
                    if(cost>1) then
                        setMessageInt("cost",cost-1)
                    end
                end
            end
        end
    end
}

Cards["Engineer Kipo"] = {
    name = "Engineer Kipo",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Machine Eater",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

    HandleMessage = function(id)
        if(getMessageType()=="post carddestroy") then
            if(getMessageInt("card")==id) then
                local ch = createChoice("Destroy a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
                ch = createChoice("Destroy a card in your mana zone",0,id,getOpponent(getCardOwner(id)),Checks.InOppMana)
                if(ch>=0) then
                    destroyCard(ch)
                end
            end
        end
    end
}

Cards["Essence Elf"] = {
    name = "Essence Elf",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

    HandleMessage = function(id)
        if(getMessageType()=="get cardcost") then
            if(getCardZone(id)==ZONE_BATTLE) then
                if(getCardType(getMessageInt("card"))==TYPE_SPELL) then
                    local cost = getMessageInt("cost")
                    if(cost>1) then
                        setMessageInt("cost",cost-1)
                    end
                end
            end
        end
    end
}

Cards["Ethel, Star Sea Elemental"] = {
    name = "Ethel, Star Sea Elemental",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 5500,
	breaker = 1,

    HandleMessage = function(id)
        Abils.cantBeBlocked(id)
    end
}

Cards["Fighter Dual Fang"] = {
    name = "Fighter Dual Fang",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

    HandleMessage = function(id)
        --todo
    end
}

Cards["Fonch, the Oracle"] = {
	name = "Fonch, the Oracle",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Light Bringer",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
            if(ch>=0) then
                tapCard(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Fortress Shell"] = {
	name = "Fortress Shell",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Colony Shell",
	cost = 9,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local ch = createChoice("Choose a card in your opponent's mana zone",0,id,getCardOwner(id),Checks.InOppMana)
            if(ch>=0) then
                destroyCard(ch)
                local ch2 = createChoice("Choose a card in your opponent's mana zone",0,id,getCardOwner(id),Checks.InOppMana)
                if(ch2>=0) then
                    destroyCard(ch2)
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Galsaur"] = {
	name = "Galsaur",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        if(Actions.countCreaturesInBattle(getCardOwner(id))<=1 and getCardZone(id)==ZONE_BATTLE) then
            Abils.PowerAttacker(id,4000)
            Abils.Breaker(id,2)
        end
	end
}

Cards["General Dark Fiend"] = {
	name = "General Dark Fiend",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Dark Lord",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a shield",0,id,getCardOwner(id),Checks.InYourShield)
            if(ch>=0) then
                destroyCard(ch)
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Gigastand"] = {
	name = "Gigastand",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Gray Balloon, Shadow of Greed"] = {
	name = "Gray Balloon, Shadow of Greed",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantAttack(id)
	end
}

Cards["Horrid Worm"] = {
	name = "Horrid Worm",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Parasite Worm",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.discardOppCardOnAttack(id,1)
	end
}

Cards["Hypersquid Walter"] = {
	name = "Hypersquid Walter",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            drawCards(getCardOwner(id),1)
        end
        Abils.onAttack(id,func)
	end
}

Cards["King Nautilus"] = {
	name = "King Nautilus",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        if(getCardZone(id)==ZONE_BATTLE) then
            local owner = getCardOwner(id)
            local size = getZoneSize(owner,ZONE_BATTLE)
            for i=0,(size-1) do
                local c = getCardAt(owner,ZONE_BATTLE,i)
                if(getCardRace(c)=="Liquid People") then
                    Abils.cantBeBlocked(c)
                end
            end
        end
	end
}

Cards["Ladia Bale, the Inspirational"] = {
	name = "Ladia Bale, the Inspirational",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 9500,
	breaker = 2,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Laguna, Lightning Enforcer"] = {
	name = "Laguna, Lightning Enforcer",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2500,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local owner = getCardOwner(id)
            openDeck(owner)
	        local ch = createChoice("Choose a spell in your deck",0,id,owner,Checks.SpellInYourDeck)
            closeDeck(owner)
	        if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                shuffleDeck(getCardOwner(ch))
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Larba Geer, the Immaculate"] = {
	name = "Larba Geer, the Immaculate",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Leaping Tornado Horn"] = {
	name = "Leaping Tornado Horn",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local c = Actions.countCreaturesInBattle(getCardOwner(id))-1
        Abils.PowerAttacker(id,c*1000)
	end
}

Cards["Logic Cube"] = {
	name = "Logic Cube",
	set = "Evo-Crushinators of Doom",
	type = TYPE_LIGHT,
	civilization = CIV_SPELL,
	cost = 3,

	shieldtrigger = 1,

	OnCast = function(id)
        local owner = getCardOwner(id)
        openDeck(owner)
	    local ch = createChoice("Choose a spell in your deck",0,id,owner,Checks.SpellInYourDeck)
        closeDeck(owner)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
            shuffleDeck(getCardOwner(ch))
        end
        Actions.EndSpell(id)
	end
}

Cards["Lost Soul"] = {
	name = "Lost Soul",
	set = "Evo-Crushinators of Doom",
	type = TYPE_LIGHT,
	civilization = CIV_DARKNESS,
	cost = 7,

	shieldtrigger = 0,

	OnCast = function(id)
        local owner = getOpponent(getCardOwner(id))
        local size = getZoneSize(owner,ZONE_HAND)
        for i=0,(size-1) do
            destroyCard(getCardAt(owner,ZONE_HAND,i))
        end
        Actions.EndSpell(id)
	end
}

Cards["Magris, Vizier of Magnetism"] = {
	name = "Magris, Vizier of Magnetism",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.drawOnSummon(id,1)
	end
}

Cards["Mana Crisis"] = {
	name = "Mana Crisis",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 4,

	shieldtrigger = 1,

	OnCast = function(id)
        local ch = createChoice("Choose a card in your opponent's mana zone",0,id,getCardOwner(id),Checks.InOppMana)
        if(ch>=0) then
            destroyCard(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Marrow Ooze, the Twister"] = {
	name = "Marrow Ooze, the Twister",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 1,

	shieldtrigger = 0,
	blocker = 1,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Metalwing Skyterror"] = {
	name = "Metalwing Skyterror",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose an opponent's blocker",1,id,getCardOwner(id),Checks.BlockerInOppBattle)
            if(ch>=0) then
                destroyCard(ch)
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Mini Titan Gett"] = {
	name = "Mini Titan Gett",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.PowerAttacker(id,1000)
        --todo
	end
}

Cards["Phal Eega, Dawn Guardian"] = {
	name = "Phal Eega, Dawn Guardian",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Guardian",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Plasma Chaser"] = {
	name = "Plasma Chaser",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            drawCards(getCardOwner(id),Actions.countCreaturesInBattle(getOpponent(getCardOwner(id))))
        end
        Abils.onAttack(id,func)
	end
}

Cards["Poison Worm"] = {
	name = "Poison Worm",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Parasite Worm",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Rainbow Stone"] = {
	name = "Rainbow Stone",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        local owner = getCardOwner(id)
        openDeck(owner) 
        local ch = createChoice("Choose a card in your deck",0,id,owner,Checks.InYourDeck)
        closeDeck(owner)
        if(ch>=0) then
            moveCard(ch,ZONE_MANA)
        end
        Actions.EndSpell(id)
	end
}

Cards["Recon Operation"] = {
	name = "Recon Operation",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 2,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Reso Pacos, Clear Sky Guardian"] = {
	name = "Reso Pacos, Clear Sky Guardian",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Rumble Gate"] = {
	name = "Rumble Gate",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Rumbling Terahorn"] = {
	name = "Rumbling Terahorn",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
    race = "Horned Beast",
	cost = 5,

	shieldtrigger = 0,
    blocker = 0,

    power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        func = function(id)
            local owner = getCardOwner(id)
            openDeck(owner)
	        local ch = createChoice("Choose a creature in your deck",0,id,owner,Checks.CreatureInYourDeck)
            closeDeck(owner)
	        if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                shuffleDeck(getCardOwner(ch))
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Scissor Eye"] = {
	name = "Scissor Eye",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
    race = "Gel Fish",
	cost = 4,

	shieldtrigger = 0,
    blocker = 0,

    power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Silver Axe"] = {
	name = "Silver Axe",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
    race = "Beast Folk",
	cost = 3,

	shieldtrigger = 0,
    blocker = 0,

    power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local turn = getTurn()
			local size = getZoneSize(turn,ZONE_BATTLE)
			local c = getCardAt(turn,ZONE_DECK,size-1)
			moveCard(c,ZONE_MANA)
        end
        Abils.onAttack(id,func)
	end
}

Cards["Silver Fist"] = {
	name = "Silver Fist",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
    race = "Beast Folk",
	cost = 4,

	shieldtrigger = 0,
    blocker = 0,

    power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.PowerAttacker(id,2000)
	end
}

Cards["Spiral Grass"] = {
	name = "Spiral Grass",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
    race = "Starlight Tree",
	cost = 4,

	shieldtrigger = 0,
    blocker = 1,

    power = 2500,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Stained Glass"] = {
	name = "Stained Glass",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
    race = "Cyber Virus",
	cost = 3,

	shieldtrigger = 0,
    blocker = 0,

    power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Thought Probe"] = {
	name = "Thought Probe",
	set = "Evo-Crushinators of Doom",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Ultracide Worm"] = {
	name = "Ultracide Worm",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
    race = "Parasite Worm",
	cost = 6,

	shieldtrigger = 0,
    blocker = 0,

    power = 11000,
	breaker = 2,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Wyn, the Oracle"] = {
	name = "Wyn, the Oracle",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
    race = "Light Bringer",
	cost = 2,

	shieldtrigger = 0,
    blocker = 0,

    power = 1500,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Xeno Mantis"] = {
	name = "Xeno Mantis",
	set = "Evo-Crushinators of Doom",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
    race = "Giant Insect",
	cost = 7,

	shieldtrigger = 0,
    blocker = 0,

    power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.cantBeBlockedPower(id,5000)
	end
}




