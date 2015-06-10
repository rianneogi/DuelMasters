package.path = package.path .. ';./?.lua;'
require("EvoCrushinators")

Cards["Alek, Solidity Enforcer"] = {
	name = "Alek, Solidity Enforcer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker",
	cost = 7,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturepower") then
            if(getMessageInt("creature")==id) then
                local valid = function(cid,sid)
                    if(getCardOwner(cid)==getCardOwner(sid) and getCardZone(cid)==ZONE_BATTLE and getCardZone(sid)==ZONE_BATTLE and getCardCiv(sid)==CIV_LIGHT and cid~=sid) then
                        return 1
                    else
                        return 0
                    end
                end
                local c = Actions.count(id,valid)
                Abils.bonusPower(id,c*1000)
            end
        end
	end
}

Cards["Aless, the Oracle"] = {
	name = "Aless, the Oracle",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Light Bringer",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="mod creaturedestroy") then
		    if(getMessageInt("creature")==id and getCardZone(id)==ZONE_BATTLE) then
			    setMessageInt("zoneto",ZONE_SHIELD)
		    end
	    end
	end
}

Cards["Angler Cluster"] = {
	name = "Angler Cluster",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Cluster",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantAttack(id)
        --todo
	end
}

Cards["Aqua Deformer"] = {
	name = "Aqua Deformer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            for i=1,2 do
                local ch = createChoice("Choose a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
                if(ch>=0) then
                    moveCard(ch,ZONE_HAND)
                end
            end
            for i=1,2 do
                local ch = createChoice("Choose a card in your mana zone",0,id,getOpponent(getCardOwner(id)),Checks.InOppMana)
                if(ch>=0) then
                    moveCard(ch,ZONE_HAND)
                end
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Armored Warrior Quelos"] = {
	name = "Armored Warrior Quelos",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armoloid",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local valid1 = function(cid,sid)
                if(getCardOwner(sid)==getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardCiv(sid)==CIV_FIRE) then
		            return 1
	            else
		            return 0
	            end
            end
            local ch1 = createChoice("Choose a non-fire card in your mana zone",0,id,getCardOwner(id),valid1)
            if(ch1>=0) then
                destroyMana(ch1)
            end

            local valid2 = function(cid,sid)
                if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_MANA and getCardCiv(sid)==CIV_FIRE) then
		            return 1
	            else
		            return 0
	            end
            end
            local ch2 = createChoice("Choose a non-fire card in your mana zone",0,id,getCardOwner(id),valid2)
            if(ch2>=0) then
                destroyMana(ch2)
            end
        end
	end
}

Cards["Aurora of Reversal"] = {
	name = "Aurora of Reversal",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 5,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Baby Zoppe"] = {
	name = "Baby Zoppe",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Fire Bird",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Baraga, Blade of Gloom"] = {
	name = "Baraga, Blade of Gloom",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Dark Lord",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Blaze Cannon"] = {
	name = "Blaze Cannon",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 7,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Boltail Dragon"] = {
	name = "Alek, Solidity Enforcer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 9000,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Bone Piercer"] = {
	name = "Bone Piercer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Bone Piercer",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="post cardmove") then
            if(getMessageInt("from")==ZONE_BATTLE and getMessageInt("to")==ZONE_GRAVEYARD) then
                local ch = createChoice("Choose a creature in your mana zone",1,id,getCardOwner(id),Checks.CreatureInYourMana)
                if(ch>=0) then
                    moveCard(ch,ZONE_HAND)
                end
            end
        end
	end
}

Cards["Boomerang Comet"] = {
	name = "Boomerang Comet",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 6,

	shieldtrigger = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Chaos Fish"] = {
	name = "Chaos Fish",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Dawn Giant"] = {
	name = "Dawn Giant",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 11000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.cantAttackCreatures(id)
	end
}

Cards["Earthstomp Giant"] = {
	name = "Earthstomp Giant",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
        local func = function(id)
            local func2 = function(cid,sid)
                moveCard(sid,ZONE_HAND)
            end
            Actions.execute(id,Checks.CreatureInYourMana,func2)
        end
        Abils.onAttack(id,func)
	end
}

Cards["Eldritch Poison"] = {
	name = "Eldritch Poison",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 1,

	shieldtrigger = 1,

	OnCast = function(id)
        local valid = function(cid,sid)
            if(Checks.InYourBattle(cid,sid)==1 and getCardCiv(sid)==CIV_DARKNESS) then
                return 1
            else
                return 0
            end
        end
        local ch = createChoice("Destroy one of your darkness creatures",1,id,getCardOwner(id),valid)
        if(ch>=0) then  
            destroyCreature(ch)
            local ch2 = createChoice("Choose a creature in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
            if(ch2>=0) then
                moveCard(ch2,ZONE_HAND)
            end
        end
        Actions.EndSpell(id)
	end
}

Cards["Emeral"] = {
	name = "Emeral",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Lord",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Explosive Dude Joe"] = {
	name = "Explosive Dude Joe",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Flametropus"] = {
	name = "Flametropus",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a card in your mana zone",1,id,getCardOwner(id),Checks.InYourMana)
            if(ch>=0) then
                destroyMana(ch)
                local mod = function(cid,mid)
                    Abils.PowerAttacker(cid,3000)
                    Abils.Breaker(cid,2)
		            Abils.destroyModAtEOT(cid,mid)
                end
                createModifier(id,mod)
            end
        end
	end
}

Cards["Flood Valve"] = {
	name = "Alek, Solidity Enforcer",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 2,

	shieldtrigger = 1,

	OnCast = function(id)
        local ch = createChoice("Choose a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
        if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Actions.EndSpell(id)
	end
}

Cards["Gamil, Knight of Hatred"] = {
	name = "Gamil, Knight of Hatred",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local valid = function(cid,sid)
                if(Checks.CreatureInYourGraveyard(cid,sid) and getCardCiv(sid)==CIV_DARKNESS) then
                    return 1
                else
                    return 0
                end
            end
            for i=1,count do
                local ch = createChoice("Select a darkness creature in your graveyard",0,id,getCardOwner(id),valid)
                if(ch>=0) then
                    moveCard(ch,ZONE_HAND)
                end
            end
        end
        Abils.onAttack(id,func)
	end
}

Cards["Garkago Dragon"] = {
	name = "Garkago Dragon",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.canAttackUntappedCreatures(id)
        --todo
	end
}

Cards["Ghastly Drain"] = {
	name = "Ghastly Drain",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 3,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Gigamantis"] = {
	name = "Alek, Solidity Enforcer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.Evolution(id)
        local owner = getCardOwner(id)
        local s = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(s-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardCiv(cid)==CIV_NATURE and cid~=id) then
                Abils.manaAfterDestroyed(cid)
            end
        end
	end
}

Cards["Giriel, Ghastly Warrior"] = {
	name = "Alek, Solidity Enforcer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 11000,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Hang Worm, Fetid Larva"] = {
	name = "Hang Worm, Fetid Larva",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Parasite Worm",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Jack Viper, Shadow of Doom"] = {
	name = "Jack Viper, Shadow of Doom",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.Evolution(id)
        local owner = getCardOwner(id)
        local s = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(s-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardCiv(cid)==CIV_DARKNESS and cid~=id) then
                Abils.returnAfterDestroyed(cid)
            end
        end
	end
}

Cards["King Neptas"] = {
	name = "King Neptas",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["King Ponitas"] = {
	name = "King Ponitas",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Legendary Bynor"] = {
	name = "Legendary Bynor",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.Evolution(id)
        local owner = getCardOwner(id)
        local s = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(s-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardCiv(cid)==CIV_WATER and cid~=id) then
                Abils.cantBeBlocked(cid)
            end
        end
	end
}

Cards["Lena, Vizier of Brilliance"] = {
	name = "Lena, Vizier of Brilliance",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        local func = function(id)
            local ch = createChoice("Choose a spell in your mana zone",1,id,getCardOwner(id),Checks.SpellsInYourMana)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Liquid Scope"] = {
	name = "Liquid Scope",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 4,

	shieldtrigger = 1,

	OnCast = function(id)
        --todo
	end
}

Cards["Logic Sphere"] = {
	name = "Logic Sphere",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 3,

	shieldtrigger = 1,

	OnCast = function(id)
        local ch = createChoice("Choose a spell in your mana zone",0,id,getCardOwner(id),Checks.SpellsInYourMana)
        if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Actions.EndSpell(id)
	end
}

Cards["Mana Nexus"] = {
	name = "Mana Nexus",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	cost = 4,

    shieldtrigger = 1,  

	OnCast = function(id)
        local ch = createChoice("Choose a card in your mana zone",0,id,getCardOwner(id),Checks.InYourMana)
        if(ch>=0) then
            moveCard(ch,ZONE_SHIELD)
        end
        Actions.EndSpell(id)
	end
}

Cards["Miar, Comet Elemental"] = {
	name = "Miar, Comet Elemental",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 11500,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Mudman"] = {
	name = "Mudman",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Hedrian",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Muramasa, Duke of Blades"] = {
	name = "Muramasa, Duke of Blades",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Pouch Shell"] = {
	name = "Pouch Shell",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Colony Beetle",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Psychic Shaper"] = {
	name = "Psychic Shaper",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	race = "Initiate",
	cost = 6,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Psyshroom"] = {
	name = "Psyshroom",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Balloon Mushroom",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Ra Vu, Seeker of Lightning"] = {
	name = "Ra Vu, Seeker of Lightning",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Mecha Thunder",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Raging Dash-Horn"] = {
	name = "Raging Dash-Horn",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Raza Vega, Thunder Guardian"] = {
	name = "Raza Vega, Thunder Guardian",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 10,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="mod creaturedestroy") then
		    if(getMessageInt("creature")==id and getCardZone(id)==ZONE_BATTLE) then
			    setMessageInt("zoneto",ZONE_SHIELD)
		    end
	    end
	end
}

Cards["Roar of the Earth"] = {
	name = "Raza Vega, Thunder Guardian",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 2,

	shieldtrigger = 1,

	OnCast = function(id)
        --todo
	end
}

Cards["Scratchclaw"] = {
	name = "Scratchclaw",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Hedrian",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.Slayer(id)
        --todo
	end
}

Cards["Searing Wave"] = {
	name = "Searing Wave",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 5,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Shtra"] = {
	name = "Shtra",
	set = "Rampage of the Super Warriors",
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

Cards["Sieg Balicula, the Intense"] = {
	name = "Sieg Balicula, the Intense",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.Evolution(id)
        local owner = getCardOwner(id)
        local s = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(s-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardCiv(cid)==CIV_LIGHT and cid~=id) then
                Abils.Blocker(cid)
            end
        end
	end
}

Cards["Snake Attack"] = {
	name = "Snake Attack",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        --todo
	end
}

Cards["Snip Striker Bullraizer"] = {
	name = "Snip Striker Bullraizer",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Sniper Mosquito"] = {
	name = "Sniper Mosquito",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 1,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Sparkle Flower"] = {
	name = "Sparkle Flower",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Starlight Tree",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Stinger Ball"] = {
	name = "Stinger Ball",
	set = "Rampage of the Super Warriors",
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

Cards["Sundrop Armor"] = {
	name = "Sundrop Armor",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 4,

	shieldtrigger = 0,

	OnCast = function(id)
        local ch = createChoice("Choose a card in your hand",0,id,getCardOwner(id),Checks.InYourHand)
        if(ch>=0) then
            moveCard(ch,ZONE_SHIELD)
        end
        Actions.EndSpell(id)
	end
}

Cards["Sword Butterfly"] = {
	name = "Sword Butterfly",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.PowerAttack(id,3000)
	end
}

Cards["Uberdragon Jabaha"] = {
	name = "Uberdragon Jabaha",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 11000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.Evolution(id)
        local owner = getCardOwner(id)
        local s = getZoneSize(owner,ZONE_BATTLE)
        for i=0,(s-1) do
            local cid = getCardAt(owner,ZONE_BATTLE,i)
            if(getCardCiv(cid)==CIV_FIRE and cid~=id) then
                Abils.PowerAttacker(cid,2000)
            end
        end
	end
}

Cards["Ur Pale, Seeker of Sunlight"] = {
	name = "Ur Pale, Seeker of Sunlight",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Mecha Thunder",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2500,
	breaker = 1,

	HandleMessage = function(id)
        --todo
	end
}

Cards["Volcanic Arrows"] = {
	name = "Volcanic Arrows",
	set = "Rampage of the Super Warriors",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 2,

	shieldtrigger = 1,

	OnCast = function(id)
        --todo
	end
}

Cards["Wailing Shadow Belbetphlo"] = {
	name = "Wailing Shadow Belbetphlo",
	set = "Rampage of the Super Warriors",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.Slayer(id)
	end
}

