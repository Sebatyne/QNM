#include "NotesExporter.h"

namespace NM{
    QString LaTexNotesExporter::NoteToLatex(Note * ConvertedNote, unsigned int titleLevel){
        QString latexExport;
        (titleLevel > titleSize.size() - 1) ? titleLevel = titleSize.size() - 1 : titleLevel;
        if(ConvertedNote->getType() == Note::Document){
            Document * tdoc = dynamic_cast<Document*>(ConvertedNote);
            if(tdoc){

                if(titleLevel > 0){
                    latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + tdoc->getTitle() + "}\n\n";
                }

                Document::Iterator it = tdoc->begin();

                for(; it != tdoc->end(); it++){
                    latexExport += NoteToLatex(*it, titleLevel + 1);
                }

                if(delimitParts){
                    latexExport += "\\rule{\\linewidth}{.5pt}\n\n";
                }

            }
        }
        else if(ConvertedNote->getType() == Note::NArticle)
        {
            NArticle * tArt = dynamic_cast<NArticle*>(ConvertedNote);
            if(tArt){
                latexExport += ArticleToLatex(tArt, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NImage){
            NImage * tIm = dynamic_cast<NImage*>(ConvertedNote);
            if(tIm){
                latexExport += ImageToLatex(tIm, titleLevel);
            }
        }
        else if(!ignoreAudio && ConvertedNote->getType() == Note::NAudio)
        {
            NAudio * tAud = dynamic_cast<NAudio*>(ConvertedNote);
            if(tAud){
                latexExport += AudioToLatex(tAud, titleLevel);
            }
        }
        else if(!ignoreVideo && ConvertedNote->getType() == Note::NVideo){
            NVideo * tVid = dynamic_cast<NVideo*>(ConvertedNote);
            if(tVid){
                latexExport += VideoToLatex(tVid, titleLevel);
            }
        }
        return latexExport;
    }

    QString LaTexNotesExporter::ArticleToLatex(NArticle * ConvertedArticle, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedArticle->getTitle() + "}";
        }
        latexExport += ConvertedArticle->getText() + "\\\\";

        return latexExport;
    }

    QString LaTexNotesExporter::ImageToLatex(NImage * ConvertedImage, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedImage->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 1]{" + ConvertedImage->getUrl() + "}\n";
        latexExport += "\\caption{" + ConvertedImage->getDescription() + "}";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::AudioToLatex(NAudio * ConvertedAudio, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedAudio->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 0.5]{aud.jpg}\n";
        latexExport += "\\caption{Fichier Audio"+ ConvertedAudio->getDescription() +"\\\\Ecouter: "+ ConvertedAudio->getUrl() +"}\n";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::VideoToLatex(NVideo * ConvertedVideo, unsigned int titleLevel){
        QString latexExport = "";
        if(titleLevel){
            latexExport += "\\" + titleSize[titleLevel] + (!ignoreNumbering ? "" : "*") + "{" + ConvertedVideo->getTitle() + "}\n\n";
        }
        latexExport += "\\begin{figure}[h!]\n";
        latexExport += "\\centering\n";
        latexExport += "\\includegraphics[scale = 0.5]{vid.jpg}\n";
        latexExport += "\\caption{Fichier Video : "+ ConvertedVideo->getDescription() +"\\\\Regarder: "+ ConvertedVideo->getUrl() +"}\n";
        latexExport += "\\end{figure}\n\n";

        return latexExport;
    }

    QString LaTexNotesExporter::getRawExport(){
        QString latexExport = "\\documentclass[12pt,a4paper]{article}\n"; // Changer Article par le type de document choisi
        latexExport += "\\usepackage[latin1]{inputenc}\n";
        latexExport += "\\usepackage[T1]{fontenc}\n";
        latexExport += "\\usepackage[francais]{babel}\n";
        latexExport += "\\usepackage{courier}\n";
        latexExport += "\\usepackage{caption}\n";
        latexExport += "\\usepackage{graphicx}\n";
        latexExport += "\\usepackage[top=1cm, bottom=2cm, right=1.5cm, left=1.5cm]{geometry}\n\n";
        latexExport += "\\title{"+ ExportedNote->getTitle() +"}\n\n";

         latexExport += "\\date{";
        if(displayDate){
            latexExport += "\\date\\today";
        }
        latexExport += "}";

        latexExport += "\\begin{document}\n\n";
        latexExport += "\\maketitle\n\n";
        latexExport += NoteToLatex(this->ExportedNote, 0);

        latexExport += "\\end{document}";

        return latexExport;
    }



    /*class textNotesExporter : NotesExporter{
    public:
        textNotesExporter(Note * ExportedNote) : NotesExporter(ExportedNote){}
        QString getRawExport();
    };*/


    QString textNotesExporter::NoteToText(Note * ConvertedNote, unsigned int titleLevel){
        QString textExport;
        if(ConvertedNote->getType() == Note::Document){
            Document * tdoc = dynamic_cast<Document*>(ConvertedNote);
            if(tdoc){

                textExport += "\n";

                if(titleLevel > 0){
                    textExport += NUtils::repeat(titleLevel, "\t") + "[" + tdoc->getTitle() + "]\n\n";
                }

                Document::Iterator it = tdoc->begin();

                for(; it != tdoc->end(); it++){
                    textExport += NoteToText(*it, titleLevel + 1);
                }

                if(delimitParts){
                    textExport += "_________________________________________________________________________________\n\n";
                }

            }
        }
        else if(ConvertedNote->getType() == Note::NArticle)
        {
            NArticle * tArt = dynamic_cast<NArticle*>(ConvertedNote);
            if(tArt){
                textExport += ArticleToText(tArt, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NImage){
            NImage * tIm = dynamic_cast<NImage*>(ConvertedNote);
            if(tIm){
                textExport += ImageToText(tIm, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NAudio)
        {
            NAudio * tAud = dynamic_cast<NAudio*>(ConvertedNote);
            if(tAud){
                textExport += AudioToText(tAud, titleLevel);
            }
        }
        else if(ConvertedNote->getType() == Note::NVideo){
            NVideo * tVid = dynamic_cast<NVideo*>(ConvertedNote);
            if(tVid){
                textExport += VideoToText(tVid, titleLevel);
            }
        }
        return textExport;
    }

    QString textNotesExporter::ArticleToText(NArticle * ConvertedArticle, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedArticle->getTitle() + "]\n";
        }
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedArticle->getText() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::ImageToText(NImage * ConvertedImage, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedImage->getTitle() + "]\n\n";
        }
        textExport += NUtils::repeat(titleLevel, "\t") + "Voir " + ConvertedImage->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedImage->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::AudioToText(NAudio * ConvertedAudio, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedAudio->getTitle() + "]\n\n";
        }

        textExport += NUtils::repeat(titleLevel, "\t") + "Ecouter " + ConvertedAudio->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedAudio->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::VideoToText(NVideo * ConvertedVideo, unsigned int titleLevel){
        QString textExport = "";
        if(titleLevel){
            textExport += NUtils::repeat(titleLevel, "\t") + "[" + ConvertedVideo->getTitle() + "]\n\n";
        }

        textExport += NUtils::repeat(titleLevel, "\t") + "Regarder " + ConvertedVideo->getUrl() + "\n";
        textExport += NUtils::repeat(titleLevel, "\t") + ConvertedVideo->getDescription() + "\n\n";

        return textExport;
    }

    QString textNotesExporter::getRawExport(){
        QString textExport = NUtils::repeat(5, "\t") + " ********** " +ExportedNote->getTitle() + " **********\n";
        if(displayDate){
            textExport += "Le @@@@@@@@ \n\n"; //Remplacer par la date
        }
        textExport += "\n\n";

        textExport += NoteToText(this->ExportedNote, 0);

        return textExport;
    }


}
