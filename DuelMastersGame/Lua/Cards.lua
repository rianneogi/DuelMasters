Cards = {}

package.path = package.path .. ';./?.lua;'
require("Survivors")

loadCards = function()
	for k,v in pairs(Cards) do loadcard(k,v.set) end
end

getCardData = function(card,value)
	return Cards[card].value
end
