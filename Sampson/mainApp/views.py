from django.shortcuts import render
from django.http import HttpResponseRedirect
from django.contrib import auth
from django.template.context_processors import csrf
from django.template import RequestContext
from django.shortcuts import render
from .models import Client, Medication, Alert
# Create your views here.

def login(request):
	context = RequestContext(request)
	if request.method == 'POST':
		username = request.POST.get('username', '')
		password = request.POST.get('password', '')
		user = auth.authenticate(username=username, password=password)
		
		if user is not None:
			if user.is_active:
				auth.login(request, user)
				return HttpResponseRedirect('/home')
			else:
				return HttpResponse("Your account is not currently active.")
		else:
			#print: "Invalid login details: {0}, {1}".format(username, password)
			return HttpResponse("Invalid login details supplied.")
	else:
		return render(request,'base.html',{})

def home(request):
	clients=Client.objects.all()
	context={'clients':clients}
	if request.user.is_authenticated():
		return render(request,'MyFinancials.html',context)
	else:
		return render(request,'registration/login.html',{})
