def is_valid_IPv4(ip):
    segments = ip.split('.')
    if len(segments)!= 4:
        return False

    for segment in segments:
        if not segment.isdigit():
            return False
        if not (0 <= int(segment) <= 255):
            return False

    return True

print("SUBNETTING AND SUBNET MASK")
IP = input("Enter IP Address: ")
if is_valid_IPv4(IP):
    IP_components = IP.split('.')
    class_check = int(IP_components[0])
    mask = ""
    if(class_check>0):
        if(class_check<=127):
            mask = "255.0.0.0"
            print("Class A IP Address")
            print("SUBNET MASK: ",mask)
        elif(128<=class_check<=191):
            mask = "255.255.0.0"
            print("Class B IP Address")
            print("SUBNET MASK: ",mask)
        elif(192<=class_check<=223):
            mask = "255.255.255.0"
            print("CLass C IP Address")
            print("SUBNET MASK: ",mask)
        elif(224<=class_check<=239):
            mask = "255.0.0.0"
            print("Class D IP Address")
            print("SUBNET MASK: ",mask)
        elif(240<=class_check<=254):
            mask = "255.0.0.0"
            print("Class E IP Address")
            print("SUBNET MASK: ",mask)
else:
    print("Invalid IP Address")
