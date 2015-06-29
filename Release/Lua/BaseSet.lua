package.path = package.path .. ';./?.lua;'
require("Common")

Cards["Aqua Hulcus"] = {
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
}

Cards["Aqua Knight"] = {
	name = "Aqua Knight",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Aqua Sniper"] = {
	name = "Aqua Sniper",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose 2 creatures",0,id,getCardOwner(id),Checks.InBattle)
            if(ch>=0) then   
                moveCard(ch,ZONE_HAND)
                local ch2 = createChoice("Choose 2 creatures",0,id,getCardOwner(id),Checks.InBattle)
                if(ch2>=0) then
                    moveCard(ch2,ZONE_HAND)
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Aqua Soldier"] = {
	name = "Aqua Soldier",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Aqua Vehicle"] = {
	name = "Aqua Vehicle",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Liquid People",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Armored Walker Urherion"] = {
	name = "Armored Walker Urherion",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armorloid",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id and getAttacker()==id) then
				local owner = getCardOwner(id)
				local size = getZoneSize(owner,ZONE_BATTLE)-1
				for i=0,size,1 do
					if(isCreatureOfRace(getCardAt(owner,ZONE_BATTLE,i),"Human")==1) then
						setMessageInt("power",getMessageInt("power")+2000)
						break
					end
				end
			end
		end
	end
}

Cards["Artisan Picora"] = {
	name = "Artisan Picora",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Machine Eater",
	cost = 1,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.destroyYourManaOnSummon(id,1)
	end
}

Cards["Astrocomet Dragon"] = {
	name = "Astrocomet Dragon",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,4000)
	end
}

Cards["Aura Blast"] = {
	name = "Aura Blast",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 4,
	shieldtrigger = 0,

	OnCast = function(id)
        local mod = function(cid,mid)
            Abils.PowerAttacker(cid,2000)
		    Abils.destroyModAtEOT(cid,mid)
        end
        local func = function(cid,sid)
            createModifier(sid,mod)
        end
		Actions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        Actions.EndSpell(id)
	end
}

Cards["Black Feather, Shadow of Rage"] = {
	name = "Black Feather, Shadow of Rage",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 1,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local c = createChoice("Select creature to destroy",0,id,getCardOwner(id),Checks.InYourBattle)
            if(c>=0) then
                destroyCreature(c)
            end
            if(c==RETURN_NOVALID or c==RETURN_SKIP) then
                destroyCreature(id)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Bloody Squito"] = {
	name = "Bloody Squito",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Brain Jacker",
	cost = 2,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
		Abils.destroyAfterBattle(id)
	end
}

Cards["Bolshack Dragon"] = {
	name = "Bolshack Dragon",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Dragon",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id and getAttacker()==id) then
				local count = 0
				local owner = getCardOwner(id)
				local size = getZoneSize(owner,ZONE_GRAVEYARD)-1
				for i=0,size,1 do
					if(getCardCiv(getCardAt(owner,ZONE_GRAVEYARD,i))==CIV_FIRE) then
						count = count+1
					end
				end
				setMessageInt("power",getMessageInt("power")+(count*1000))
			end
		end
	end
}

Cards["Bone Assassin, the Ripper"] = {
	name = "Bone Assassin, the Ripper",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Slayer(id)
	end
}

Cards["Bone Spider"] = {
	name = "Bone Spider",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.destroyAfterBattle(id)
	end
}

Cards["Brain Serum"] = {
	name = "Brain Serum",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 4,
	shieldtrigger = 1,

    OnCast = function(id)
        drawCards(getCardOwner(id),2)
        Actions.EndSpell(id)
    end
}

Cards["Brawler Zyler"] = {
	name = "Brawler Zyler",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Bronze-Arm Tribe"] = {
	name = "Bronze-Arm Tribe",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            Actions.moveTopCardsFromDeck(getCardOwner(id),ZONE_MANA,1)
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Burning Mane"] = {
	name = "Burning Mane",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Burning Power"] = {
	name = "Burning Power",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 1,
	shieldtrigger = 0,

	OnCast = function(id)
        local mod = function(cid,mid)
            Abils.PowerAttacker(cid,2000)
		    Abils.destroyModAtEOT(cid,mid)
        end
		local c = createChoice("Choose creature",0,id,getCardOwner(id),Checks.InYourBattle)
		if(c>=0) then
            createModifier(c,mod)
        end
        Actions.EndSpell(id)
	end
}

Cards["Candy Drop"] = {
	name = "Candy Drop",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Virus",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
	end
}

Cards["Chaos Strike"] = {
	name = "Chaos Strike",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 2,
	shieldtrigger = 0,

    OnCast = function(id)
        local mod = function(cid,mid)
            if(getMessageType()=="get creaturecanattackcreature") then
			    if(getMessageInt("defender")==cid) then
				    setMessageInt("canattack",CANATTACK_UNTAPPED)
			    end
		    end
		    Abils.destroyModAtEOT(cid,mid)
        end
		local c = createChoice("Choose creature",0,id,getCardOwner(id),Checks.InOppBattle)
		if(c>=0) then
            createModifier(c,mod)
        end
        Actions.EndSpell(id)
	end
}

Cards["Chilias, the Oracle"] = {
	name = "Chilias, the Oracle",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Light Bringer",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2500,
	breaker = 1,

	HandleMessage = function(id)
		Abils.returnAfterDestroyed(id)
	end
}

Cards["Coiling Vines"] = {
	name = "Coiling Vines",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.manaAfterDestroyed(id)
	end
}

Cards["Creeping Plague"] = {
	name = "Creeping Plague",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 1,
	shieldtrigger = 0,

    OnCast = function(id)
        local mod1 = function(cid,mid)
            local mod2 = function(cid,mid)
                Abils.Slayer(cid)
                Abils.destroyModAtEOT(cid,mid)
            end
            if(getMessageType()=="creatureblock") then
                if(getMessageInt("attacker")==cid) then
                    createModifier(cid,mod2)
                end
            end
		    Abils.destroyModAtEOT(cid,mid)
        end
        local func = function(cid,sid)
            createModifier(sid,mod1)
        end
		Actions.executeForCreaturesInBattle(id,getCardOwner(id),func)
        Actions.EndSpell(id)
	end
}

Cards["Crimson Hammer"] = {
	name = "Crimson Hammer",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 2,
	shieldtrigger = 0,

    OnCast = function(id)
        local valid = function(cid,sid)
            if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=2000) then
		        return 1
	        else
		        return 0
	        end
        end
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),valid)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Crystal Memory"] = {
	name = "Crystal Memory",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 4,
	shieldtrigger = 1,

    OnCast = function(id)
        local owner = getCardOwner(id)
        openDeck(owner)
	    local ch = createChoice("Choose a card in your deck",0,id,owner,Checks.InYourDeck)
        closeDeck(owner)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
            shuffleDeck(owner)
        end
        Actions.EndSpell(id)
	end
}

Cards["Dark Clown"] = {
	name = "Dark Clown",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Brain Jacker",
	cost = 4,

	shieldtrigger = 0,
	blocker = 1,

	power = 6000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
		Abils.destroyAfterBattle(id)
	end
}

Cards["Dark Raven, Shadow of Grief"] = {
	name = "Dark Raven, Shadow of Grief",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 4,

	shieldtrigger = 0,
	blocker = 1,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Dark Reversal"] = {
	name = "Dark Reversal",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 2,
	shieldtrigger = 1,

    OnCast = function(id)
        local ch = createChoice("Choose a creature in your graveyard",0,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
        if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Actions.EndSpell(id)
    end
}

Cards["Deadly Fighter Braid Claw"] = {
	name = "Deadly Fighter Braid Claw",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 1,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.attacksEachTurn(id)
	end
}

Cards["Death Smoke"] = {
	name = "Death Smoke",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 4,
	shieldtrigger = 0,

	OnCast = function(id)
	    local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.UntappedInOppBattle)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Deathblade Beetle"] = {
	name = "Deathblade Beetle",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,4000)
	end
}

Cards["Deathliger, Lion of Chaos"] = {
	name = "Deathliger, Lion of Chaos",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 9000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Dia Nork, Moonlight Guardian"] = {
	name = "Dia Nork, Moonlight Guardian",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 4,

	shieldtrigger = 0,
	blocker = 1,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Dimension Gate"] = {
	name = "Dimension Gate",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 3,
	shieldtrigger = 1,

    OnCast = function(id)
        local owner = getCardOwner(id)
        openDeck(owner)
	    local ch = createChoice("Choose a creature in your deck",0,id,owner,Checks.CreatureInYourDeck)
        closeDeck(owner)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
            shuffleDeck(owner)
        end
        Actions.EndSpell(id)
	end
}

Cards["Dome Shell"] = {
	name = "Dome Shell",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Colony Beetle",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Draglide"] = {
	name = "Draglide",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.attacksEachTurn(id)
	end
}

Cards["Emerald Grass"] = {
	name = "Emerald Grass",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Starlight Tree",
	cost = 2,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Explosive Fighter Ucarn"] = {
	name = "Explosive Fighter Ucarn",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 9000,
	breaker = 2,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose 2 cards in the mana zone",0,id,getCardOwner(id),Checks.InYourMana)
            if(ch>=0) then   
                destroyMana(ch)
                local ch2 = createChoice("Choose 2 cards in the mana zone",0,id,getCardOwner(id),Checks.InYourMana)
                if(ch2>=0) then
                    destroyMana(ch2)
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Faerie Child"] = {
	name = "Faerie Child",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Virus",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
	end
}

Cards["Fatal Attacker Horvath"] = {
	name = "Fatal Attacker Horvath",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id and getAttacker()==id) then
				local owner = getCardOwner(id)
				local size = getZoneSize(owner,ZONE_BATTLE)-1
				for i=0,size,1 do
					if(isCreatureOfRace(getCardAt(owner,ZONE_BATTLE,i),"Armorloid")==1) then
						setMessageInt("power",getMessageInt("power")+2000)
						break
					end
				end
			end
		end
	end
}

Cards["Fear Fang"] = {
	name = "Fear Fang",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Fire Sweeper Burning Hellion"] = {
	name = "Fire Sweeper Burning Hellion",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Forest Hornet"] = {
	name = "Forest Hornet",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Frei, Vizier of Air"] = {
	name = "Frei, Vizier of Air",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.untapAtEOT(id)
	end
}

Cards["Gatling Skyterror"] = {
	name = "Gatling Skyterror",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
		Abils.canAttackUntappedCreatures(id)
	end
}

Cards["Ghost Touch"] = {
	name = "Ghost Touch",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 2,
	shieldtrigger = 1,

    OnCast = function(id)
        discardCardAtRandom(getOpponent(getCardOwner(id)))
        Actions.EndSpell(id)
    end
}

Cards["Gigaberos"] = {
	name = "Gigaberos",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose 2 creatures in your battle zone",0,id,getCardOwner(id),Checks.InYourBattle)
            if(ch>=0) then
                if(ch==id) then
                    destroyCreature(id)
                else
                    destroyCreature(ch)
                    local ch2 = createChoice("Choose 2 creatures in your battle zone",0,id,getCardOwner(id),Checks.InYourBattle)
                    if(ch2>=0) then
                        destroyCreature(ch2)
                    end
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Gigagiele"] = {
	name = "Gigagiele",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.Slayer(id)
	end
}

Cards["Gigargon"] = {
	name = "Gigargon",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Chimera",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose 2 creatures in your graveyard",1,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
                local ch2 = createChoice("Choose 2 creatures in your graveyard",1,id,getCardOwner(id),Checks.CreatureInYourGraveyard)
                if(ch2>=0) then
                    moveCard(ch2,ZONE_HAND)
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Golden Wing Striker"] = {
	name = "Golden Wing Striker",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Gran Gure, Space Guardian"] = {
	name = "Gran Gure, Space Guardian",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 9000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Hanusa, Radiance Elemental"] = {
	name = "Hanusa, Radiance Elemental",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 9500,
	breaker = 2,

	HandleMessage = function(id)
	end
}

Cards["Holy Awe"] = {
	name = "Holy Awe",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 6,
	shieldtrigger = 1,

	OnCast = function(id)
		local owner = getCardOwner(id)
		local opp = getOpponent(owner)
		local size = getZoneSize(opp,ZONE_BATTLE)-1
		for i=0,size,1 do
			tapCard(getCardAt(opp,ZONE_BATTLE,i))
		end
        Actions.EndSpell(id)
	end
}

Cards["Hunter Fish"] = {
	name = "Hunter Fish",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Fish",
	cost = 2,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Iere, Vizier of Bullets"] = {
	name = "Iere, Vizier of Bullets",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Illusionary Merfolk"] = {
	name = "Illusionary Merfolk",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local owner = getCardOwner(id)
			local size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				if(isCreatureOfRace(getCardAt(owner,ZONE_BATTLE,i),"Cyber Lord")==1) then
					drawCards(owner,3)
					break
				end
			end
		end
		Abils.onSummon(id,func)
	end
}

Cards["Immortal Baron, Vorg"] = {
	name = "Immortal Baron, Vorg",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Human",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Iocant, the Oracle"] = {
	name = "Iocant, the Oracle",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Light Bringer",
	cost = 2,

	shieldtrigger = 0,
	blocker = 1,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="get creaturepower") then
			if(getMessageInt("creature")==id) then
				local owner = getCardOwner(id)
				local size = getZoneSize(owner,ZONE_BATTLE)-1
				for i=0,size,1 do
					if(isCreatureOfRace(getCardAt(owner,ZONE_BATTLE,i),"Angel Command")==1) then
						setMessageInt("power",getMessageInt("power")+2000)
						break
					end
				end
			end
		end
		Abils.cantAttackPlayers(id)
	end
}

Cards["King Coral"] = {
	name = "King Coral",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["King Depthcon"] = {
	name = "King Depthcon",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
		Abils.cantBeBlocked(id)
	end
}

Cards["King Ripped-Hide"] = {
	name = "King Ripped-Hide",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Leviathan",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="post cardmove") then
			if(getMessageInt("card")==id) then
				if(getMessageInt("to")==ZONE_BATTLE) then
					drawCards(getCardOwner(id),2)
				end
			end
		end
	end
}

Cards["La Ura Giga, Sky Guardian"] = {
	name = "La Ura Giga, Sky Guardian",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 1,

	shieldtrigger = 0,
	blocker = 1,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Lah, Purification Enforcer"] = {
	name = "Lah, Purification Enforcer",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 5500,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Laser Wing"] = {
	name = "Laser Wing",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 5,
	shieldtrigger = 0,

    OnCast = function(id)
        local mod = function(cid,mid)
            Abils.cantBeBlocked(cid)
	        Abils.destroyModAtEOT(cid,mid)
        end
        local ch = createChoice("Choose 2 of your creatures",0,id,getCardOwner(id),Checks.InYourBattle)
        if(ch>=0) then
            createModifier(ch,mod)
            local ch2 = createChoice("Choose 2 of your creatures",0,id,getCardOwner(id),Checks.InYourBattle)
            if(ch2>=0) then
                 createModifier(ch2,mod)
            end
        end
        Actions.EndSpell(id)
	end
}

Cards["Lok, Vizier of Hunting"] = {
	name = "Lok, Vizier of Hunting",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Magma Gazer"] = {
	name = "Magma Gazer",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 3,
	shieldtrigger = 0,

    OnCast = function(id)
        local mod = function(cid,mid)
            Abils.PowerAttacker(cid,4000)
            Abils.Breaker(cid,2)
		    Abils.destroyModAtEOT(cid,mid)
        end
		local ch = createChoice("Choose creature",0,id,getCardOwner(id),Checks.InYourBattle)
		if(ch>=0) then
            createModifier(ch,mod)
        end
        Actions.EndSpell(id)
	end
}

Cards["Marine Flower"] = {
	name = "Marine Flower",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Virus",
	cost = 1,

	shieldtrigger = 0,
	blocker = 1,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Masked Horror, Shadow of Scorn"] = {
	name = "Masked Horror, Shadow of Scorn",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            discardCardAtRandom(getOpponent(getCardOwner(id)))
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Meteosaur"] = {
	name = "Meteosaur",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            valid = function(cid,sid)
                if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=2000) then
		            return 1
	            else
		            return 0
	            end
            end
            local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),valid)
            if(ch>=0) then
                destroyCreature(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Miele, Vizier of Lightning"] = {
	name = "Miele, Vizier of Lightning",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose an opponent's creature",1,id,getCardOwner(id),Checks.UntappedInOppBattle)
            if(ch>=0) then
                tapCard(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Mighty Shouter"] = {
	name = "Mighty Shouter",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.manaAfterDestroyed(id)
	end
}

Cards["Moonlight Flash"] = {
	name = "Moonlight Flash",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 4,
	shieldtrigger = 0,

    OnCast = function(id)
        local ch = createChoice("Choose 2 of your opponent's creatures",0,id,getCardOwner(id),Checks.InOppBattle)
        if(ch>=0) then
            tapCard(ch)
            local ch2 = createChoice("Choose 2 of your opponent's creatures",0,id,getCardOwner(id),Checks.InOppBattle)
            if(ch2>=0) then
                tapCard(ch2)
            end
        end
        Actions.EndSpell(id)
	end
}

Cards["Natural Snare"] = {
	name = "Natural Snare",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 6,
	shieldtrigger = 1,

    OnCast = function(id)
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.InOppBattle)
        if(ch>=0) then
            moveCard(ch,ZONE_MANA)
        end
	    Actions.EndSpell(id)
	end
}

Cards["Night Master, Shadow of Decay"] = {
	name = "Night Master, Shadow of Decay",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Ghost",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,
	breaker = 1
}

Cards["Nomad Hero Gigio"] = {
	name = "Nomad Hero Gigio",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Machine Eater",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.canAttackUntappedCreatures(id)
	end
}

Cards["Onslaughter Triceps"] = {
	name = "Onslaughter Triceps",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.destroyYourManaOnSummon(id,1)
	end
}

Cards["Pangaea's Song"] = {
	name = "Pangaea's Song",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 1,
	shieldtrigger = 0,

    OnCast = function(id)
        createChoice("Choose a creature in your battle zone",0,id,getCardOwner(id),Checks.InYourBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_MANA)
        end
        Actions.EndSpell(id)
    end
}

Cards["Phantom Fish"] = {
	name = "Phantom Fish",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Poisonous Dahlia"] = {
	name = "Poisonous Dahlia",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Poisonous Mushroom"] = {
	name = "Poisonous Mushroom",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Choose a card in your hand",1,id,getCardOwner(id),Checks.InYourHand)
            if(ch>=0) then
                moveCard(ch,ZONE_MANA)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Rayla, Truth Enforcer"] = {
	name = "Rayla, Truth Enforcer",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Berserker",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local owner = getCardOwner(id)
            openDeck(owner)
            local ch = createChoice("Choose a spell in your deck",1,id,owner,Checks.SpellInYourDeck)
            closeDeck(owner)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
            shuffleDeck(ch,owner)
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Red-Eye Scorpion"] = {
	name = "Red-Eye Scorpion",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Giant Insect",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.manaAfterDestroyed(id)
	end
}

Cards["Reusol, the Oracle"] = {
	name = "Reusol, the Oracle",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Revolver Fish"] = {
	name = "Revolver Fish",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 4,

	shieldtrigger = 0,
	blocker = 1,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Roaring Great-Horn"] = {
	name = "Roaring Great-Horn",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 8000,
	breaker = 2,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Rothus, the Traveler"] = {
	name = "Rothus, the Traveler",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armorloid",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        local summon = function(id)
            local ch = createChoice("Select creature to destroy",0,id,getCardOwner(id),Checks.InYourBattle)
            if(ch>=0) then
                destroyCreature(ch)
                local ch2 = createChoice("Select creature to destroy",0,id,getOpponent(getCardOwner(id)),Checks.InOppBattle)
                if(ch2>=0) then
                    destroyCreature(ch2)
                end
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Ruby Grass"] = {
    name = "Ruby Grass",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Starlight Tree",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 3000,

    HandleMessage = function(id)
        Abils.untapAtEOT(id)
        Abils.cantAttackPlayers(id)
	end
}

Cards["Saucer-Head Shark"] = {
	name = "Saucer-Head Shark",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Gel Fish",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local owner = getCardOwner(id)
			local size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreaturePower(cid)<=2000) then
					moveCard(cid,ZONE_HAND)
				end
			end
			owner = getOpponent(getCardOwner(id))
			size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreaturePower(cid)<=2000) then
					moveCard(cid,ZONE_HAND)
				end
			end
        end
        Abils.onSummon(id,func)
	end
}

Cards["Scarlet Skyterror"] = {
	name = "Scarlet Skyterror",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Armored Wyvern",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local owner = getCardOwner(id)
			local size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreatureIsBlocker(cid)==1) then
					destroyCreature(cid)
				end
			end

			owner = getOpponent(getCardOwner(id))
			size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreatureIsBlocker(cid)==1) then
					destroyCreature(cid)
				end
			end
		end
        Abils.onSummon(id,func)
	end
}

Cards["Seamine"] = {
	name = "Seamine",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Fish",
	cost = 6,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Senatine Jade Tree"] = {
	name = "Senatine Jade Tree",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Starlight Tree",
	cost = 3,

	shieldtrigger = 0,
	blocker = 1,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Skeleton Soldier, the Defiled"] = {
	name = "Skeleton Soldier, the Defiled",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Solar Ray"] = {
	name = "Solar Ray",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 2,
	shieldtrigger = 1,

    OnCast = function(id)
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.UntappedInOppBattle)
        if(ch>=0) then
            tapCard(ch)
        end
	    Actions.EndSpell(id)
	end
}

Cards["Sonic Wing"] = {
	name = "Sonic Wing",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_LIGHT,
	cost = 3,
	shieldtrigger = 0,

    OnCast = function(id)
        local mod = function(cid,mid)
            Abils.cantBeBlocked(cid)
	        Abils.destroyModAtEOT(cid,mid)
        end
		local ch = createChoice("Choose creature",0,id,getCardOwner(id),Checks.InYourBattle)
		if(ch>=0) then
            createModifier(ch,mod)
        end
        Actions.EndSpell(id)
	end
}

Cards["Spiral Gate"] = {
	name = "Spiral Gate",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 2,
	shieldtrigger = 1,

    OnCast = function(id)
        local ch = createChoice("Choose a creature",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
        end
        Actions.EndSpell(id)
	end
}

Cards["Stampeding Longhorn"] = {
	name = "Stampeding Longhorn",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantBeBlockedPower(id,3000)
	end
}


Cards["Steel Smasher"] = {
	name = "Steel Smasher",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Beast Folk",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Stinger Worm"] = {
	name = "Stinger Worm",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Parasite Worm",
	cost = 3,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local ch = createChoice("Destroy a creature",0,id,getCardOwner(id),Checks.InYourBattle)
            if(ch>=0) then
                destroyCreature(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Stonesaur"] = {
	name = "Stonesaur",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Rock Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,2000)
	end
}

Cards["Storm Shell"] = {
	name = "Storm Shell",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Colony Beetle",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local ch = createChoice("Choose a creature",0,id,getOpponent(getCardOwner(id)),Checks.InOppBattle)
            if(ch>=0) then
                moveCard(ch,ZONE_MANA)
            end
        end
        Abils.onSummon(id,summon)
	end,

    Select = function(cid,sid)
        moveCard(sid,ZONE_MANA)
        setChoiceActive(0)
    end
}

Cards["Super Explosive Volcanodon"] = {
	name = "Super Explosive Volcanodon",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_FIRE,
	race = "Dragonoid",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.PowerAttacker(id,4000)
	end
}

Cards["Swamp Worm"] = {
	name = "Swamp Worm",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Parasite Worm",
	cost = 7,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		summon = function(id)
            local ch = createChoice("Choose a creature",0,id,getOpponent(getCardOwner(id)),Checks.InOppBattle)
            if(ch>=0) then
                destroyCreature(ch)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Szubs Kin, Twilight Guardian"] = {
	name = "Szubs Kin, Twilight Guardian",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Guardian",
	cost = 5,

	shieldtrigger = 0,
	blocker = 1,

	power = 6000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttackPlayers(id)
	end
}

Cards["Teleportation"] = {
	name = "Teleportation",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 5,
	shieldtrigger = 0,

    OnCast = function(id)
        local ch = createChoice("Choose 2 creatures",0,id,getCardOwner(id),Checks.InBattle)
	    if(ch>=0) then
            moveCard(ch,ZONE_HAND)
            local ch2 = createChoice("Choose 2 creatures",0,id,getCardOwner(id),Checks.InBattle)
            if(ch2>=0) then
                moveCard(ch2,ZONE_HAND)
            end
        end
        Actions.EndSpell(id)
	end
}

Cards["Terror Pit"] = {
	name = "Terror Pit",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_DARKNESS,
	cost = 6,
	shieldtrigger = 1,

    OnCast = function(id)
	    local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.InOppBattle)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Thorny Mandra"] = {
	name = "Thorny Mandra",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Tree Folk",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		if(getMessageType()=="post cardmove") then
            if(getMessageInt("card")==id) then
			    createChoice("Thorny Mandra: Select card in graveyard",1,id)
			    choicePushSelect(3,"Cards","Thorny Mandra","Select")
                choicePushButton1(2,"Actions","SkipChoice")
			    choicePushValid(2,"Checks","InYourGraveyard")
            end
		end
        summon = function(id)
            local ch = createChoice("Select card in graveyard",1,id,getCardOwner(id),Checks.InYourGraveyard)
            if(ch>=0) then
                moveCard(ch,ZONE_MANA)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Toel, Vizier of Hope"] = {
	name = "Toel, Vizier of Hope",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Initiate",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="pre endturn") then
		    if(getMessageInt("player")==getCardOwner(id) and getCardZone(id)==ZONE_BATTLE) then
			    local ch = createChoiceNoCheck("Untap creatures?",2,id,getCardOwner(id),Checks.False)
			    if(ch==RETURN_BUTTON1) then
                    local owner = getCardOwner(cid)
		            local size = getZoneSize(owner,ZONE_BATTLE)-1
		            for i=0,size,1 do
		                local cid = getCardAt(owner,ZONE_BATTLE,i)
		                untapCard(cid)
		            end
                end
		    end
	    end
	end
}

Cards["Tornado Flame"] = {
	name = "Tornado Flame",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_FIRE,
	cost = 5,
	shieldtrigger = 1,

    OnCast = function(id)
        local valid = function(cid,sid)
            if(getCardOwner(sid)~=getCardOwner(cid) and getCardZone(sid)==ZONE_BATTLE and getCreaturePower(sid)<=4000) then
		        return 1
	        else
		        return 0
	        end
        end
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),valid)
	    if(ch>=0) then
            destroyCreature(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Tower Shell"] = {
	name = "Tower Shell",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Colony Beetle",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
        Abils.cantBeBlockedPower(id,4000)
	end
}

Cards["Tri-horn Shepherd"] = {
	name = "Tri-horn Shepherd",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_NATURE,
	race = "Horned Beast",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 5000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Tropico"] = {
	name = "Tropico",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Cyber Lord",
	cost = 5,

	shieldtrigger = 0,
	blocker = 0,

	power = 3000,
	breaker = 1,

	HandleMessage = function(id)
        if(getMessageType()=="get creaturecanbeblocked") then
            if(getMessageInt("creature")==id) then
                if(getZoneSize(getCardOwner(id),ZONE_BATTLE)>=3) then
                    setMessageInt("canbeblocked",0)
                end
            end
        end
	end
}

Cards["Ultimate Force"] = {
	name = "Ultimate Force",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_NATURE,
	cost = 5,
	shieldtrigger = 0,

    OnCast = function(id)
        local turn = getTurn()
		local size = getZoneSize(turn,ZONE_BATTLE)
		local c = getCardAt(turn,ZONE_DECK,size-1)
		moveCard(c,ZONE_MANA)
        c = getCardAt(turn,ZONE_DECK,size-2)
        moveCard(c,ZONE_MANA)
        Actions.EndSpell(id)
    end
}

Cards["Unicorn Fish"] = {
	name = "Unicorn Fish",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_WATER,
	race = "Fish",
	cost = 4,

	shieldtrigger = 0,
	blocker = 0,

	power = 1000,
	breaker = 1,

	HandleMessage = function(id)
        summon = function(id)
            local ch = createChoice("Choose a creature",1,id,getCardOwner(id),Checks.InBattle)
            if(ch>=0) then
                moveCard(ch,ZONE_HAND)
            end
        end
        Abils.onSummon(id,summon)
	end
}

Cards["Urth, Purifying Elemental"] = {
	name = "Urth, Purifying Elemental",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_LIGHT,
	race = "Angel Command",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 6000,
	breaker = 2,

	HandleMessage = function(id)
        Abils.untapAtEOT(id)
	end
}

Cards["Vampire Silphy"] = {
	name = "Vampire Silphy",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Dark Lord",
	cost = 8,

	shieldtrigger = 0,
	blocker = 0,

	power = 4000,
	breaker = 1,

	HandleMessage = function(id)
		local func = function(id)
			local owner = getCardOwner(id)
			local size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreaturePower(cid)<=3000) then
					destroyCreature(cid)
				end
			end

			owner = getOpponent(getCardOwner(id))
			size = getZoneSize(owner,ZONE_BATTLE)-1
			for i=0,size,1 do
				local cid = getCardAt(owner,ZONE_BATTLE,i)
				if(getCreaturePower(cid)<=3000) then
					destroyCreature(cid)
				end
			end
		end
        Abils.onSummon(id,func)
	end
}

Cards["Virtual Tripwire"] = {
	name = "Virtual Tripwire",
	set = "Base Set",
	type = TYPE_SPELL,
	civilization = CIV_WATER,
	cost = 3,
	shieldtrigger = 0,

    OnCast = function(id)
        local ch = createChoice("Choose an opponent's creature",0,id,getCardOwner(id),Checks.UntappedInOppBattle)
	    if(ch>=0) then
            tapCard(ch)
        end
        Actions.EndSpell(id)
	end
}

Cards["Wandering Braineater"] = {
	name = "Wandering Braineater",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 2,

	shieldtrigger = 0,
	blocker = 1,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
		Abils.cantAttack(id)
	end
}

Cards["Writhing Bone Ghoul"] = {
	name = "Writhing Bone Ghoul",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Living Dead",
	cost = 2,

	shieldtrigger = 0,
	blocker = 0,

	power = 2000,
	breaker = 1,

	HandleMessage = function(id)
	end
}

Cards["Zagaan, Knight of Darkness"] = {
	name = "Zagaan, Knight of Darkness",
	set = "Base Set",
	type = TYPE_CREATURE,
	civilization = CIV_DARKNESS,
	race = "Demon Command",
	cost = 6,

	shieldtrigger = 0,
	blocker = 0,

	power = 7000,
	breaker = 2,

	HandleMessage = function(id)
	end
}