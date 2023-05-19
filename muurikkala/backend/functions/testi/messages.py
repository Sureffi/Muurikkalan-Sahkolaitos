from twilio.rest import Client




class Message:
    def __init__(self, twilio_sid, twilio_auth, twilio_pn) -> None:
        self.TWILIO_SID = twilio_sid
        self.TWILIO_AUTH = twilio_auth
        self.TWILIO_PN = twilio_pn
        self.TO_PN = ['+358451508780', '+358408480938', '+358440427454']
        # maria '+358408480938'
        # iska '+358440427454'
        
        self.client = Client(self.TWILIO_SID, self.TWILIO_AUTH)
        
    
    def akku_jannite(self, jannite: float = None):
        viesti = f'!HÄLYTYS!\nAkun varaus matala ({jannite}V)'
        for number in self.TO_PN:
            message = self.client.messages.create(
                body=viesti,
                from_=self.TWILIO_PN,
                to=number
            )
    
    
    def pinta(self, taso: int = None):
        if 75 < taso < 90:
            viesti = f'!HÄLYTYS!\nPinnan taso alle 90% ({taso}%)'
        elif taso < 75:
            viesti = f'!HÄLYTYS!\nPinnan taso alle 75% ({taso}%)'
        
        for number in self.TO_PN:
            message = self.client.messages.create(
                body=viesti,
                from_=self.TWILIO_PN,
                to=number
            )
        
            
    def automaatti_muutos(self, tila: bool):
        if tila == True:
            viesti = f'Automaatin tila muutettu\nTila: päällä'
        else:
             viesti = f'Automaatin tila muutettu\nTila: pois'
            
        for number in self.TO_PN:
            message = self.client.messages.create(
                body=viesti,
                from_=self.TWILIO_PN,
                to=number
            )
        
            
            
TWILIO_SID = 'AC6ac1b7afb294e88582fd07bbcb16139e'
TWILIO_AUTH = '5444a0216562cd6d68b0624a556e5de9'
TWILIO_PN = '+358 45 4907451'
messager = Message(TWILIO_SID, TWILIO_AUTH, TWILIO_PN)

messager.pinta(80)
messager.pinta(60)
messager.automaatti_muutos(True)
messager.akku_jannite(23.4)