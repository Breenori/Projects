from django.db import models

# Create your models here.


# Types (Skriptsprachen im WWW, Bibliotheken, etc..)
class ScriptTypes(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50)

# Holds the basic information for each language
class ScriptLangs(models.Model):
    id = models.AutoField(primary_key=True)
    name = models.CharField(max_length=50)
    desc = models.TextField()
    type = models.ForeignKey(ScriptTypes, on_delete=models.CASCADE)

# holds additional info parsed from the respective wikipedia page
class ScriptLangsAdd(models.Model):
    id = models.AutoField(primary_key=True)
    field = models.TextField(default="")
    info = models.TextField(default="")
    lang = models.ForeignKey(ScriptLangs, on_delete=models.CASCADE)

