lua_example
=====

```
local done = false
local findenum = false
local findb = false;
local finde = false;


function stringsplit(l)
	--local a,b,c,d,e = string.match(l,"(%g+)(.*=)(%s*)(.+)(,.*)")
	local a,b,c,d,e = string.match(l,"(%g+)(.*=)(%s*)(.[0-9a-zA-Z_]+)(,.*)")
	return a,d,e
end

local outf = io.open("lout.txt","w")
print("outf = ",outf)
for line in io.lines("e:/MC2GSProtocol.h") do
	if done == true then
		break
	end
	
	repeat 
		print(line)
		print(type(line))
		
		--print(io.read("*n"))
		
		if not findenum then
			if string.find(line,"enum")  then 
				findenum = true
				break
			end
			
			if findenum == false then
				break
			end
		end
		
		if not findb then 
			if string.find(line,"{")  then
				findb = true
				break
			end
			
			if findb == false then 
				break;
			end
		end
		
		if string.find(line,"}") then 
			done = true
			break
		end	
		
		local a,b,c = stringsplit(line)
		print("a=",a,"b=",b,"c= ",c)
		if a then
			outf:write(a,"=",b,"\n")
			outf:flush()
		end
	until true	
end
```
