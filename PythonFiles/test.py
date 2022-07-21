from robot import robot

MicroBot = robot()
EE = MicroBot.calculate_forward_kinematics([0.0, 0.0, 0.0, 0.0, 0.0], 4)
print(EE)