import random

random_names = ['John', 'Emily', 'Michael', 'Sarah', 'Christopher', 'Samantha', 'William', 'Olivia', 'David', 'Emma', 'Matthew', 'Ashley', 'James', 'Elizabeth', 'Benjamin', 'Isabella', 'Daniel', 'Madison', 'Joseph', 'Ava', 'Andrew', 'Mia', 'Nicholas', 'Sophia', 'Jacob', 'Chloe', 'Joshua', 'Natalie', 'Ethan', 'Grace', 'Ryan', 'Lily', 'Tyler', 'Alyssa', 'Dylan', 'Hailey', 'Brandon', 'Abigail', 'Jonathan', 'Hannah', 'Kevin', 'Victoria', 'Justin', 'Kayla', 'Zachary', 'Lauren', 'Caleb', 'Jessica', 'Anthony', 'Taylor', 'Alexander', 'Sydney', 'Christopher', 'Megan', 'Patrick', 'Rachel', 'Timothy', 'Amber', 'Sean', 'Kaitlyn', 'Cody', 'Rebecca', 'Kyle', 'Brianna', 'Eric', 'Kimberly', 'Brian', 'Mackenzie', 'Scott', 'Morgan', 'Brandon', 'Savannah', 'Austin', 'Caroline', 'Jacob', 'Ariana', 'Luke', 'Ashley', 'Evan', 'Danielle', 'Mason', 'Jennifer', 'Logan', 'Paige', 'Isaac', 'Alyson', 'Hunter', 'Maria', 'Cameron', 'Michelle', 'Devin', 'Gabriella', 'Lucas', 'Isabelle', 'Derek', 'Alexa', 'Owen', 'Catherine', 'Gavin', 'Vanessa']
provided_money = random.randint(30000,200000)
with open('output2.txt', 'w') as f:
    f.write(f"Provided money: {provided_money}\n")
    f.write("KOL Money Number_Followers Followers\n")
    for i in range(100):
        kol = random_names[i];
        number_followers = random.randint(10000, 100000)
        money = number_followers/(random.randint(10,20)) + random.randint(50,300)
        followers = ','.join(str(x) for x in random.sample(range(1, 500000), number_followers))
        f.write(f"{kol} {money} {number_followers} {{{followers}}}\n")

