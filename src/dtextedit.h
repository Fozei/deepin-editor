/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2018 Deepin, Inc.
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Rekols    <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <KF5/KSyntaxHighlighting/repository.h>
#include "uncommentselection.h"
#include "linenumberarea.h"

#include "settings.h"
#include <QAction>
#include <DMenu>
#include <QPaintEvent>
#include <DTextEdit>
#include <QPropertyAnimation>
#include <QFont>
#include <DApplicationHelper>

namespace KSyntaxHighlighting {
    class SyntaxHighlighter;
}

enum ConvertCase { UPPER, LOWER, CAPITALIZE };

class leftareaoftextedit;
class EditWrapper;
class TextEdit : public DTextEdit
{
    Q_OBJECT

public:
    enum CursorMode {
        Insert,
        Overwrite,
        Readonly
    };

    TextEdit(QWidget *parent = nullptr);

    LineNumberArea *lineNumberArea;
    leftareaoftextedit *m_pLeftAreaWidget;
    QString filepath;

    void setWrapper(EditWrapper *);

    int lineNumberAreaWidth();

    int getCurrentLine();
    int getCurrentColumn();
    int getPosition();
    int getScrollOffset();

    void forwardChar();
    void backwardChar();
    void forwardWord();
    void backwardWord();
    void forwardPair();
    void backwardPair();

    int blockCount() const;
    int characterCount() const;
    QTextBlock firstVisibleBlock();

    void moveToStart();
    void moveToEnd();
    void moveToStartOfLine();
    void moveToEndOfLine();
    void moveToLineIndentation();
    void nextLine();
    void prevLine();
    void jumpToLine(int line, bool keepLineAtCenter);

    void moveCursorNoBlink(QTextCursor::MoveOperation operation,
                           QTextCursor::MoveMode mode = QTextCursor::MoveAnchor);

    void newline();
    void openNewlineAbove();
    void openNewlineBelow();
    void moveLineDownUp(bool up);
    void scrollLineUp();
    void scrollLineDown();
    void scrollUp();
    void scrollDown();
    void duplicateLine();
    void copyLines();
    void cutlines();
    void joinLines();

    void killLine();
    void killCurrentLine();
    void killBackwardWord();
    void killForwardWord();

    void escape();
    void indentText();
    void unindentText();
    void setTabSpaceNumber(int number);
    void convertWordCase(ConvertCase convertCase);
    QString capitalizeText(QString text);

    void keepCurrentLineAtCenter();
    void scrollToLine(int scrollOffset, int row, int column);

    void setLineWrapMode(bool enable);
    void setFontFamily(QString fontName);
    void setFontSize(int fontSize);
    void updateFont();

    void replaceAll(const QString &replaceText, const QString &withText);
    void replaceNext(const QString &replaceText, const QString &withText);
    void replaceRest(const QString &replaceText, const QString &withText);

    bool findKeywordForward(const QString &keyword);

    void removeKeywords();
    bool highlightKeyword(QString keyword, int position);
    void updateCursorKeywordSelection(int position, bool findNext);
    void updateHighlightLineSelection();
    bool updateKeywordSelections(QString keyword);
    void renderAllSelections();

    DMenu *getHighlightMenu();

    void lineNumberAreaPaintEvent(QPaintEvent *event);

    void setThemeWithPath(const QString &path);
    void setTheme(const KSyntaxHighlighting::Theme &theme, const QString &path);
    void loadHighlighter();

    bool highlightWordUnderMouse(QPoint pos);
    void removeHighlightWordUnderCursor();

    void setSettings(Settings *settings);
    void setModified(bool modified);

    void copySelectedText();
    void cutSelectedText();
    void pasteText();

    void setMark();
    void unsetMark();
    bool tryUnsetMark();
    void exchangeMark();

    void saveMarkStatus();
    void restoreMarkStatus();

    void completionWord(QString word);
    QString getWordAtMouse();
    QString getWordAtCursor();

    void toggleReadOnlyMode();
    void toggleComment();

    int getNextWordPosition(QTextCursor cursor, QTextCursor::MoveMode moveMode);
    int getPrevWordPosition(QTextCursor cursor, QTextCursor::MoveMode moveMode);
    bool atWordSeparator(int position);

    void showCursorBlink();
    void hideCursorBlink();

    void setReadOnlyPermission(bool permission);
    bool getReadOnlyPermission();
    bool getReadOnlyMode();

    void hideRightMenu();

    void clearBlack();

    void bookMarkAreaPaintEvent(QPaintEvent *event);
    int getLineFromPoint(const QPoint &point);
    void addOrDeleteBookMark();
    void moveToPreviousBookMark();
    void moveToNextBookMark();

signals:
    void clickFindAction();
    void clickReplaceAction();
    void clickJumpLineAction();
    void clickFullscreenAction();
    void cursorMarkChanged(bool mark, QTextCursor cursor);
    void modificationChanged(const QString &path, bool isModified);
    void cursorModeChanged(CursorMode mode);
    void hightlightChanged(const QString &name);
    void popupNotify(QString notify);
    void click();
    void pressEsc();
    void signal_readingPath();

    void signal_clearBlack();



public slots:
    void highlightCurrentLine();
    void updateLineNumber();
    void updateWordCount();
    void handleScrollFinish();

    void clickCutAction();
    void clickCopyAction();
    void clickPasteAction();
    void clickDeleteAction();
    void clickOpenInFileManagerAction();
    void onAddBookMark();
    void onCancelBookMark();
    void onMoveToPreviousBookMark();
    void onMoveToNextBookMark();
    void onClearBookMark();

    void copyWordUnderCursor();
    void cutWordUnderCursor();

    void slot_voiceReading();
    void slot_stopReading();
    void slot_dictation();
    void slot_translate();

    void upcaseWord();
    void downcaseWord();
    void capitalizeWord();
    void transposeChar();

    void handleCursorMarkChanged(bool mark, QTextCursor cursor);

    void adjustScrollbarMargins();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void inputMethodEvent(QInputMethodEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    bool setCursorKeywordSeletoin(int position, bool findNext);
    void cursorPositionChanged();
    void updateHighlightBrackets(const QChar &openChar, const QChar &closeChar);
    int getFirstVisibleBlockId() const;

private:
    EditWrapper *m_wrapper;
    QPropertyAnimation *m_scrollAnimation;

    QList<QTextEdit::ExtraSelection> m_findMatchSelections;
    QTextEdit::ExtraSelection m_beginBracketSelection;
    QTextEdit::ExtraSelection m_endBracketSelection;
    QTextEdit::ExtraSelection m_currentLineSelection;
    QTextEdit::ExtraSelection m_findHighlightSelection;
    QTextEdit::ExtraSelection m_wordUnderCursorSelection;

    QTextCursor m_highlightWordCacheCursor;
    QTextCursor m_wordUnderPointerCursor;

    int m_lineNumberPaddingX = 5;

    int m_restoreColumn;
    int m_restoreRow;

    int m_tabSpaceNumber = 4;

    KSyntaxHighlighting::Repository m_repository;
    KSyntaxHighlighting::SyntaxHighlighter *m_highlighter;

    DMenu *m_rightMenu;
    QAction *m_undoAction;
    QAction *m_redoAction;
    QAction *m_cutAction;
    QAction *m_copyAction;
    QAction *m_pasteAction;
    QAction *m_deleteAction;
    QAction *m_selectAllAction;
    QAction *m_findAction;
    QAction *m_replaceAction;
    QAction *m_jumpLineAction;
    QAction *m_enableReadOnlyModeAction;
    QAction *m_disableReadOnlyModeAction;
    QAction *m_fullscreenAction;
    QAction *m_exitFullscreenAction;
    QAction *m_openInFileManagerAction;
    QAction *m_toggleCommentAction;
    QAction *m_voiceReadingAction;
    QAction *m_stopReadingAction;
    QAction *m_dictationAction;
    QAction *m_translateAction;
    QAction *m_addBookMarkAction;
    QAction *m_cancelBookMarkAction;
    QAction *m_clearBookMarkAction;
    QAction *m_preBookMarkAction;
    QAction *m_nextBookMarkAction;

    DMenu *m_convertCaseMenu;
    QAction *m_upcaseAction;
    QAction *m_downcaseAction;
    QAction *m_capitalizeAction;

    bool m_canUndo;
    bool m_canRedo;

    bool m_haveWordUnderCursor;

    bool m_cursorMark = false;
    int m_markStartLine = -1;

    Settings *m_settings;

    bool m_readOnlyMode = false;
    bool m_cursorMarkStatus = false;
    int m_cursorMarkPosition = 0;
    int m_cursorWidthChangeDelay = 2000;
    bool m_bReadOnlyPermission = false;

    int m_fontSize = 16;
    QString m_fontName;

    Comment::CommentDefinition m_commentDefinition;

    QStringList m_wordSepartors = QStringList({
            // English separator.
            ".", ",", "?", "!", "@", "#", "$", ":", ";", "-", "<", ">", "[", "]", "(", ")", "{", "}", "=", "/", "+", "%", "&", "^", "*", "\"", "'", "`", "~", "|", "\\", "\n",
            // Chinese separator.
            "。", "，", "？", "！", "￥", "：", "；", "《", "》", "【", "】", "（", "）", " "
        });

    QColor m_currentLineColor;
    QColor m_backgroundColor;
    QColor m_lineNumbersColor;
    QColor m_currentLineNumberColor;
    QColor m_regionMarkerColor;
    QColor m_selectionColor;
    QColor m_selectionBgColor;

    QPoint m_mouseClickPos;
    QPoint m_menuPos;

    bool m_highlighted = false;

    QTextCharFormat m_bracketMatchFormat;
    QTextCharFormat m_findMatchFormat;
    QTextCharFormat m_findHighlightFormat;
    CursorMode m_cursorMode;

    DMenu *m_hlGroupMenu;
    QActionGroup *m_hlActionGroup;

    QPoint m_lastTouchBeginPos;
    QPointer<QTimer> m_updateEnableSelectionByMouseTimer;
    int m_touchTapDistance = -1;

    QFont m_fontLineNumberArea;
    QList<int> m_listBookmark;
    int m_nLines;
};

#endif
