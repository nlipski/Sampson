from __future__ import unicode_literals
from django.db import models
from pygments.lexers import get_all_lexers
from pygments.styles import get_all_styles

LEXERS = [item for item in get_all_lexers() if item[1]]
LANGUAGE_CHOICES = sorted([(item[1][0], item[0]) for item in LEXERS])
STYLE_CHOICES = sorted((item, item) for item in get_all_styles())


class Medication (models.Model):
    name = models.CharField(max_length=100, unique=True,primary_key=True) #Like a VARCHAR field
    numLeft= models.IntegerField()
    description = models.TextField() #Like a TEXT field
    created = models.DateTimeField() #Like a DATETIME field
 
    def __unicode__(self): #Tell it to return as a unicode string (The name of the to-do 
        return self.name
		
class Alert (models.Model):
	name = models.CharField(max_length=100, unique=True,primary_key=True) #Like a VARCHAR field
	created = models.DateTimeField() #Like a DATETIME field
	intake = models.DateTimeField() #Like a DATETIME field
	description = models.TextField() #Like a TEXT field
	
class Client (models.Model):
	uid = models.IntegerField(primary_key=True) #Like a DATETIME field
	name = models.CharField(max_length=100, unique=False) #Like a VARCHAR field
	lastname = models.CharField(max_length=100, unique=True) #Like a VARCHAR field
	description = models.TextField() #Like a TEXT field
	numOfMed=models.IntegerField()
	freqOfIntake=models.IntegerField()
	medicationVal=models.ForeignKey('Medication')
	alertVal=models.ManyToManyField('Alert')
	
	def __unicode__(self):
			return self.uid
		

# Create your models here.
