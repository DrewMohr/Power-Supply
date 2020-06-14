

Notes:
    Watts = Voltage x Amperage 

Sequence path:

-Button press detected
    -Start seq
        -Testing
            -Test Fan
                -Rev to 100%
            -Test Relay0 (R0)
                -If R0 ok
                    -[OK]
                    -Send Exit=0
                -If R0 fail
                    -Send Exit=1
                    -Show Fail message
                    -[HALT]
            -Test Relay1 (R1)
                -If R1 ok
                    -[OK]
                    -Send Exit=0
                -If R1 fail
                    -Send Exit=1
                    -Show Fail message
                    -[HALT]
            -Test Voltmter/ampermeter (VAM)
                -If VAM ok
                    -[OK]
                    -Send Exit=0
                -If VAM fail
                    -Send Exit=1
                    -Show Fail message
                    -[HALT]
            -Test EEPROM/MEMORY (EEM) Read/Write
                -Addresses
                    -000 (Version Number)
                    -001 (Setting 'boot_beep')
                    -002
                    
        -Start Boot
            -EEM
                -Addr000
                    -Read --> Send to Version Var
                -Addr001
                    -Read
                        -If true
                            -'boot_beep' = true
                        -If false
                            -'boot_beep' = false

