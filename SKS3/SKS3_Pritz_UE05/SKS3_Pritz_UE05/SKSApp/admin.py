from django.contrib import admin
from SKSApp.models import ScriptTypes, ScriptLangs, ScriptLangsAdd

# Register your models here.
admin.site.register(ScriptTypes)
admin.site.register(ScriptLangs)
admin.site.register(ScriptLangsAdd)
