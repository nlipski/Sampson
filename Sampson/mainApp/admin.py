from django.contrib import admin
from .models import Client, Medication, Alert



# Register your models here.

admin.site.register(Client)
admin.site.register(Medication)
admin.site.register(Alert)
