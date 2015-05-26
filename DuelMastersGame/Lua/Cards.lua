Cards = {}

package.path = package.path .. ';./?.lua;'
require("EvoCrushinators")

loadCards = function()
	for k,v in pairs(Cards) do loadcard(k) end
end

getCardData = function(card,value)
	return Cards[card].value
end
